#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__dav_props_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {TYPE_1__* cur_dir; TYPE_3__* cur_file; void* send_all_mode; void* add_props_included; } ;
typedef  TYPE_2__ report_context_t ;
struct TYPE_12__ {char const* copyfrom_path; void* fetch_props; int /*<<< orphan*/  pool; int /*<<< orphan*/  txdelta_stream; int /*<<< orphan*/  txdelta_baton; int /*<<< orphan*/  txdelta; int /*<<< orphan*/  base_md5_checksum; void* fetch_file; int /*<<< orphan*/  final_sha1_checksum; void* copyfrom_rev; void* base_rev; } ;
typedef  TYPE_3__ file_baton_t ;
struct TYPE_13__ {char const* copyfrom_path; void* fetch_props; void* copyfrom_rev; int /*<<< orphan*/  pool; void* base_rev; } ;
typedef  TYPE_4__ dir_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_10__ {void* fetch_props; } ;

/* Variables and functions */
#define  ADD_DIR 134 
#define  ADD_FILE 133 
 void* FALSE ; 
#define  FETCH_PROPS 132 
#define  OPEN_DIR 131 
#define  OPEN_FILE 130 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_XML_ATTRIB_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
#define  TXDELTA 129 
#define  UPDATE_REPORT 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  create_dir_baton (TYPE_4__**,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_file_baton (TYPE_3__**,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_file_txdelta (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_base64_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_delta_noop_window_handler ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 void* svn_fspath__canonicalize (char const*,int /*<<< orphan*/ ) ; 
 char const* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_gather_since (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/ * svn_txdelta_parse_svndiff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
update_opened(svn_ra_serf__xml_estate_t *xes,
              void *baton,
              int entered_state,
              const svn_ra_serf__dav_props_t *tag,
              apr_pool_t *scratch_pool)
{
  report_context_t *ctx = baton;
  apr_hash_t *attrs;

  switch (entered_state)
    {
      case UPDATE_REPORT:
        {
          const char *val;

          attrs = svn_ra_serf__xml_gather_since(xes, UPDATE_REPORT);
          val = svn_hash_gets(attrs, "inline-props");

          if (val && (strcmp(val, "true") == 0))
            ctx->add_props_included = TRUE;

          val = svn_hash_gets(attrs, "send-all");

          if (val && (strcmp(val, "true") == 0))
            {
              ctx->send_all_mode = TRUE;

              /* All properties are included in send-all mode. */
              ctx->add_props_included = TRUE;
            }
        }
        break;

      case OPEN_DIR:
      case ADD_DIR:
        {
          dir_baton_t *dir;
          const char *name;
          attrs = svn_ra_serf__xml_gather_since(xes, entered_state);

          name = svn_hash_gets(attrs, "name");
          if (!name)
            name = "";

          SVN_ERR(create_dir_baton(&dir, ctx, name, scratch_pool));

          if (entered_state == OPEN_DIR)
            {
              apr_int64_t base_rev;

              SVN_ERR(svn_cstring_atoi64(&base_rev,
                                         svn_hash_gets(attrs, "rev")));
              dir->base_rev = (svn_revnum_t)base_rev;
            }
          else
            {
              dir->copyfrom_path = svn_hash_gets(attrs, "copyfrom-path");

              if (dir->copyfrom_path)
                {
                  apr_int64_t copyfrom_rev;
                  const char *copyfrom_rev_str;
                  dir->copyfrom_path = svn_fspath__canonicalize(
                                                        dir->copyfrom_path,
                                                        dir->pool);

                  copyfrom_rev_str = svn_hash_gets(attrs, "copyfrom-rev");

                  if (!copyfrom_rev_str)
                    return svn_error_createf(SVN_ERR_XML_ATTRIB_NOT_FOUND,
                                             NULL,
                                            _("Missing '%s' attribute"),
                                            "copyfrom-rev");

                  SVN_ERR(svn_cstring_atoi64(&copyfrom_rev, copyfrom_rev_str));

                  dir->copyfrom_rev = (svn_revnum_t)copyfrom_rev;
                }

              if (! ctx->add_props_included)
                dir->fetch_props = TRUE;
            }
        }
        break;
      case OPEN_FILE:
      case ADD_FILE:
        {
          file_baton_t *file;

          attrs = svn_ra_serf__xml_gather_since(xes, entered_state);

          SVN_ERR(create_file_baton(&file, ctx, svn_hash_gets(attrs, "name"),
                                    scratch_pool));

          if (entered_state == OPEN_FILE)
            {
              apr_int64_t base_rev;

              SVN_ERR(svn_cstring_atoi64(&base_rev,
                                         svn_hash_gets(attrs, "rev")));
              file->base_rev = (svn_revnum_t)base_rev;
            }
          else
            {
              const char *sha1_checksum;
              file->copyfrom_path = svn_hash_gets(attrs, "copyfrom-path");

              if (file->copyfrom_path)
                {
                  apr_int64_t copyfrom_rev;
                  const char *copyfrom_rev_str;

                  file->copyfrom_path = svn_fspath__canonicalize(
                                                        file->copyfrom_path,
                                                        file->pool);

                  copyfrom_rev_str = svn_hash_gets(attrs, "copyfrom-rev");

                  if (!copyfrom_rev_str)
                    return svn_error_createf(SVN_ERR_XML_ATTRIB_NOT_FOUND,
                                             NULL,
                                            _("Missing '%s' attribute"),
                                            "copyfrom-rev");

                  SVN_ERR(svn_cstring_atoi64(&copyfrom_rev, copyfrom_rev_str));

                  file->copyfrom_rev = (svn_revnum_t)copyfrom_rev;
                }

              sha1_checksum = svn_hash_gets(attrs, "sha1-checksum");
              if (sha1_checksum)
                {
                  SVN_ERR(svn_checksum_parse_hex(&file->final_sha1_checksum,
                                                 svn_checksum_sha1,
                                                 sha1_checksum,
                                                 file->pool));
                }

              /* If the server isn't in "send-all" mode, we should expect to
                 fetch contents for added files. */
              if (! ctx->send_all_mode)
                file->fetch_file = TRUE;

              /* If the server isn't included properties for added items,
                 we'll need to fetch them ourselves. */
              if (! ctx->add_props_included)
                file->fetch_props = TRUE;
            }
        }
        break;

      case TXDELTA:
        {
          file_baton_t *file = ctx->cur_file;
          const char *base_checksum;

          /* Pre 1.2, mod_dav_svn was using <txdelta> tags (in
             addition to <fetch-file>s and such) when *not* in
             "send-all" mode.  As a client, we're smart enough to know
             that's wrong, so we'll just ignore these tags. */
          if (! ctx->send_all_mode)
            break;

          file->fetch_file = FALSE;

          attrs = svn_ra_serf__xml_gather_since(xes, entered_state);
          base_checksum = svn_hash_gets(attrs, "base-checksum");

          if (base_checksum)
            SVN_ERR(svn_checksum_parse_hex(&file->base_md5_checksum,
                                           svn_checksum_md5, base_checksum,
                                           file->pool));

          SVN_ERR(open_file_txdelta(ctx->cur_file, scratch_pool));

          if (ctx->cur_file->txdelta != svn_delta_noop_window_handler)
            {
              svn_stream_t *decoder;

              decoder = svn_txdelta_parse_svndiff(file->txdelta,
                                                  file->txdelta_baton,
                                                  TRUE /* error early close*/,
                                                  file->pool);

              file->txdelta_stream = svn_base64_decode(decoder, file->pool);
            }
        }
        break;

      case FETCH_PROPS:
        {
          /* Subversion <= 1.6 servers will return a fetch-props element on
             open-file and open-dir when non entry props were changed in
             !send-all mode. In turn we fetch the full set of properties
             and send all of those as *changes* to the editor. So these
             editors have to be aware that they receive-non property changes.
             (In case of incomplete directories they have to be aware anyway)

             In r1063337 this behavior was changed in mod_dav_svn to always
             send property changes inline in these cases. (See issue #3657)

             Note that before that change the property changes to the last_*
             entry props were already inlined via specific xml elements. */
          if (ctx->cur_file)
            ctx->cur_file->fetch_props = TRUE;
          else if (ctx->cur_dir)
            ctx->cur_dir->fetch_props = TRUE;
        }
        break;
    }

  return SVN_NO_ERROR;
}