#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int len; void* data; } ;
typedef  TYPE_1__ svn_string_t ;
struct TYPE_14__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_MALFORMED_FILE ; 
 int SVN_KEYLINE_MAXLEN ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,void*,size_t,TYPE_1__*) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* svn_cstring_atoi (int*,char*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_file_getc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_file_read_full2 (int /*<<< orphan*/ *,void*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_read_length_line (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_hash_read(apr_hash_t *hash,
              apr_file_t *srcfile,
              apr_pool_t *pool)
{
  svn_error_t *err;
  char buf[SVN_KEYLINE_MAXLEN];
  apr_size_t num_read;
  char c;
  int first_time = 1;


  while (1)
    {
      /* Read a key length line.  Might be END, though. */
      apr_size_t len = sizeof(buf);

      err = svn_io_read_length_line(srcfile, buf, &len, pool);
      if (err && APR_STATUS_IS_EOF(err->apr_err) && first_time)
        {
          /* We got an EOF on our very first attempt to read, which
             means it's a zero-byte file.  No problem, just go home. */
          svn_error_clear(err);
          return SVN_NO_ERROR;
        }
      else if (err)
        /* Any other circumstance is a genuine error. */
        return err;

      first_time = 0;

      if (((len == 3) && (buf[0] == 'E') && (buf[1] == 'N') && (buf[2] == 'D'))
          || ((len == 9)
              && (buf[0] == 'P')
              && (buf[1] == 'R')       /* We formerly used just "END" to */
              && (buf[2] == 'O')       /* end a property hash, but later */
              && (buf[3] == 'P')       /* we added "PROPS-END", so that  */
              && (buf[4] == 'S')       /* the fs dump format would be    */
              && (buf[5] == '-')       /* more human-readable.  That's   */
              && (buf[6] == 'E')       /* why we accept either way here. */
              && (buf[7] == 'N')
              && (buf[8] == 'D')))
        {
          /* We've reached the end of the dumped hash table, so leave. */
          return SVN_NO_ERROR;
        }
      else if ((buf[0] == 'K') && (buf[1] == ' '))
        {
          size_t keylen;
          int parsed_len;
          void *keybuf;

          /* Get the length of the key */
          SVN_ERR(svn_cstring_atoi(&parsed_len, buf + 2));
          keylen = parsed_len;

          /* Now read that much into a buffer, + 1 byte for null terminator */
          keybuf = apr_palloc(pool, keylen + 1);
          SVN_ERR(svn_io_file_read_full2(srcfile,
                                         keybuf, keylen,
                                         &num_read, NULL, pool));
          ((char *) keybuf)[keylen] = '\0';

          /* Suck up extra newline after key data */
          SVN_ERR(svn_io_file_getc(&c, srcfile, pool));
          if (c != '\n')
            return svn_error_create(SVN_ERR_MALFORMED_FILE, NULL, NULL);

          /* Read a val length line */
          len = sizeof(buf);
          SVN_ERR(svn_io_read_length_line(srcfile, buf, &len, pool));

          if ((buf[0] == 'V') && (buf[1] == ' '))
            {
              svn_string_t *value = apr_palloc(pool, sizeof(*value));
              apr_size_t vallen;
              void *valbuf;

              /* Get the length of the value */
              SVN_ERR(svn_cstring_atoi(&parsed_len, buf + 2));
              vallen = parsed_len;

              /* Again, 1 extra byte for the null termination. */
              valbuf = apr_palloc(pool, vallen + 1);
              SVN_ERR(svn_io_file_read_full2(srcfile,
                                             valbuf, vallen,
                                             &num_read, NULL, pool));
              ((char *) valbuf)[vallen] = '\0';

              /* Suck up extra newline after val data */
              SVN_ERR(svn_io_file_getc(&c, srcfile, pool));
              if (c != '\n')
                return svn_error_create(SVN_ERR_MALFORMED_FILE, NULL, NULL);

              value->data = valbuf;
              value->len = vallen;

              /* The Grand Moment:  add a new hash entry! */
              apr_hash_set(hash, keybuf, keylen, value);
            }
          else
            {
              return svn_error_create(SVN_ERR_MALFORMED_FILE, NULL, NULL);
            }
        }
      else
        {
          return svn_error_create(SVN_ERR_MALFORMED_FILE, NULL, NULL);
        }
    } /* while (1) */
}