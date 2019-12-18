#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
struct TYPE_14__ {char* data; int len; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_15__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/  SVN_WC__ADM_ENTRIES ; 
 int /*<<< orphan*/  SVN__STREAM_CHUNK_SIZE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_strtoi64 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* memchr (char*,float,int) ; 
 int /*<<< orphan*/  parse_entries_xml (char const*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* read_entry (TYPE_1__**,char**,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_val (char const**,char**,char const*) ; 
 int /*<<< orphan*/  resolve_to_defaults (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ctype_isdigit (char) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int,...) ; 
 TYPE_3__* svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_string_from_stream2 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__open_adm_stream (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__read_entries_old(apr_hash_t **entries,
                         const char *dir_abspath,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  char *curp;
  const char *endp;
  svn_wc_entry_t *entry;
  svn_stream_t *stream;
  svn_string_t *buf;

  *entries = apr_hash_make(result_pool);

  /* Open the entries file. */
  SVN_ERR(svn_wc__open_adm_stream(&stream, dir_abspath, SVN_WC__ADM_ENTRIES,
                                  scratch_pool, scratch_pool));
  SVN_ERR(svn_string_from_stream2(&buf, stream, SVN__STREAM_CHUNK_SIZE,
                                  scratch_pool));

  /* We own the returned data; it is modifiable, so cast away... */
  curp = (char *)buf->data;
  endp = buf->data + buf->len;

  /* If the first byte of the file is not a digit, then it is probably in XML
     format. */
  if (curp != endp && !svn_ctype_isdigit(*curp))
    SVN_ERR(parse_entries_xml(dir_abspath, *entries, buf->data, buf->len,
                              result_pool, scratch_pool));
  else
    {
      int entryno, entries_format;
      const char *val;

      /* Read the format line from the entries file. In case we're in the
         middle of upgrading a working copy, this line will contain the
         original format pre-upgrade. */
      SVN_ERR(read_val(&val, &curp, endp));
      if (val)
        entries_format = (int)apr_strtoi64(val, NULL, 0);
      else
        return svn_error_createf(SVN_ERR_WC_CORRUPT, NULL,
                                 _("Invalid version line in entries file "
                                   "of '%s'"),
                                 svn_dirent_local_style(dir_abspath,
                                                        scratch_pool));
      entryno = 1;

      while (curp != endp)
        {
          svn_error_t *err = read_entry(&entry, &curp, endp,
                                        entries_format, result_pool);
          if (! err)
            {
              /* We allow extra fields at the end of the line, for
                 extensibility. */
              curp = memchr(curp, '\f', endp - curp);
              if (! curp)
                err = svn_error_create(SVN_ERR_WC_CORRUPT, NULL,
                                       _("Missing entry terminator"));
              if (! err && (curp == endp || *(++curp) != '\n'))
                err = svn_error_create(SVN_ERR_WC_CORRUPT, NULL,
                                       _("Invalid entry terminator"));
            }
          if (err)
            return svn_error_createf(err->apr_err, err,
                                     _("Error at entry %d in entries file for "
                                       "'%s':"),
                                     entryno,
                                     svn_dirent_local_style(dir_abspath,
                                                            scratch_pool));

          ++curp;
          ++entryno;

          svn_hash_sets(*entries, entry->name, entry);
        }
    }

  /* Fill in any implied fields. */
  return svn_error_trace(resolve_to_defaults(*entries, result_pool));
}