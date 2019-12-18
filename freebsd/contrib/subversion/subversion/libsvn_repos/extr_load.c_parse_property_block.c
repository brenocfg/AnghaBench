#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ len; char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_9__ {char* data; scalar_t__ len; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* delete_node_property ) (void*,char*) ;int /*<<< orphan*/  (* set_revision_property ) (void*,char*,TYPE_2__*) ;int /*<<< orphan*/  (* set_node_property ) (void*,char*,TYPE_2__*) ;} ;
typedef  TYPE_3__ svn_repos_parse_fns3_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SIZE_MAX ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  read_key_or_val (char**,scalar_t__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/ * stream_malformed () ; 
 int /*<<< orphan*/ * stream_ran_dry () ; 
 int /*<<< orphan*/  stub1 (void*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (void*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (void*,char*) ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,char*) ; 
 int /*<<< orphan*/  svn_cstring_strtoui64 (scalar_t__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_property_block(svn_stream_t *stream,
                     svn_filesize_t content_length,
                     const svn_repos_parse_fns3_t *parse_fns,
                     void *record_baton,
                     void *parse_baton,
                     svn_boolean_t is_node,
                     svn_filesize_t *actual_length,
                     apr_pool_t *pool)
{
  svn_stringbuf_t *strbuf;
  apr_pool_t *proppool = svn_pool_create(pool);

  *actual_length = 0;
  while (content_length != *actual_length)
    {
      char *buf;  /* a pointer into the stringbuf's data */
      svn_boolean_t eof;

      svn_pool_clear(proppool);

      /* Read a key length line.  (Actually, it might be PROPS_END). */
      SVN_ERR(svn_stream_readline(stream, &strbuf, "\n", &eof, proppool));

      if (eof)
        {
          /* We could just use stream_ran_dry() or stream_malformed(),
             but better to give a non-generic property block error. */
          return svn_error_create
            (SVN_ERR_STREAM_MALFORMED_DATA, NULL,
             _("Incomplete or unterminated property block"));
        }

      *actual_length += (strbuf->len + 1); /* +1 because we read a \n too. */
      buf = strbuf->data;

      if (! strcmp(buf, "PROPS-END"))
        break; /* no more properties. */

      else if ((buf[0] == 'K') && (buf[1] == ' '))
        {
          char *keybuf;
          apr_uint64_t len;

          SVN_ERR(svn_cstring_strtoui64(&len, buf + 2, 0, APR_SIZE_MAX, 10));
          SVN_ERR(read_key_or_val(&keybuf, actual_length,
                                  stream, (apr_size_t)len, proppool));

          /* Read a val length line */
          SVN_ERR(svn_stream_readline(stream, &strbuf, "\n", &eof, proppool));
          if (eof)
            return stream_ran_dry();

          *actual_length += (strbuf->len + 1); /* +1 because we read \n too */
          buf = strbuf->data;

          if ((buf[0] == 'V') && (buf[1] == ' '))
            {
              svn_string_t propstring;
              char *valbuf;
              apr_int64_t val;

              SVN_ERR(svn_cstring_atoi64(&val, buf + 2));
              propstring.len = (apr_size_t)val;
              SVN_ERR(read_key_or_val(&valbuf, actual_length,
                                      stream, propstring.len, proppool));
              propstring.data = valbuf;

              /* Now, send the property pair to the vtable! */
              if (is_node)
                {
                  SVN_ERR(parse_fns->set_node_property(record_baton,
                                                       keybuf,
                                                       &propstring));
                }
              else
                {
                  SVN_ERR(parse_fns->set_revision_property(record_baton,
                                                           keybuf,
                                                           &propstring));
                }
            }
          else
            return stream_malformed(); /* didn't find expected 'V' line */
        }
      else if ((buf[0] == 'D') && (buf[1] == ' '))
        {
          char *keybuf;
          apr_uint64_t len;

          SVN_ERR(svn_cstring_strtoui64(&len, buf + 2, 0, APR_SIZE_MAX, 10));
          SVN_ERR(read_key_or_val(&keybuf, actual_length,
                                  stream, (apr_size_t)len, proppool));

          /* We don't expect these in revision properties, and if we see
             one when we don't have a delete_node_property callback,
             then we're seeing a v3 feature in a v2 dump. */
          if (!is_node || !parse_fns->delete_node_property)
            return stream_malformed();

          SVN_ERR(parse_fns->delete_node_property(record_baton, keybuf));
        }
      else
        return stream_malformed(); /* didn't find expected 'K' line */

    } /* while (1) */

  svn_pool_destroy(proppool);
  return SVN_NO_ERROR;
}