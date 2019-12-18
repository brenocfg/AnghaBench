#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {int /*<<< orphan*/ * last_author; int /*<<< orphan*/  time; int /*<<< orphan*/  created_rev; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; int /*<<< orphan*/  has_props; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ svn_dirent_t ;
struct TYPE_11__ {int /*<<< orphan*/ * author; int /*<<< orphan*/  receiver_baton; int /*<<< orphan*/  (* receiver ) (char const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_4__* author_buf; } ;
typedef  TYPE_3__ list_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int AUTHOR ; 
 int /*<<< orphan*/  FALSE ; 
 int ITEM ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_MALFORMED_DATA ; 
 int /*<<< orphan*/  SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (char const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_base64_decode_string (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash__get_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_node_kind_from_word (char const*) ; 
 int /*<<< orphan*/  svn_revnum_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_set (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
item_closed(svn_ra_serf__xml_estate_t *xes,
            void *baton,
            int leaving_state,
            const svn_string_t *cdata,
            apr_hash_t *attrs,
            apr_pool_t *scratch_pool)
{
  list_context_t *list_ctx = baton;

  if (leaving_state == AUTHOR)
    {
      /* For compatibility with liveprops, current servers will not use
       * base64-encoding for "binary" user names bu simply drop the
       * offending control chars.
       *
       * We might want to switch to revprop-style encoding, though,
       * and this is the code to do that. */
      const char *encoding = svn_hash_gets(attrs, "encoding");
      if (encoding)
        {
          /* Check for a known encoding type.  This is easy -- there's
             only one.  */
          if (strcmp(encoding, "base64") != 0)
            {
              return svn_error_createf(SVN_ERR_RA_DAV_MALFORMED_DATA, NULL,
                                       _("Unsupported encoding '%s'"),
                                       encoding);
            }

          cdata = svn_base64_decode_string(cdata, scratch_pool);
        }

      /* Remember until the next ITEM closing tag. */
      svn_stringbuf_set(list_ctx->author_buf, cdata->data);
      list_ctx->author = list_ctx->author_buf->data;
    }
  else if (leaving_state == ITEM)
    {
      const char *dirent_path = cdata->data;
      const char *kind_word, *date, *crev, *size;
      svn_dirent_t dirent = { 0 };

      kind_word = svn_hash_gets(attrs, "node-kind");
      size = svn_hash_gets(attrs, "size");

      dirent.has_props = svn_hash__get_bool(attrs, "has-props", FALSE);
      crev = svn_hash_gets(attrs, "created-rev");
      date = svn_hash_gets(attrs, "date");

      /* Convert data. */
      dirent.kind = svn_node_kind_from_word(kind_word);

      if (size)
        SVN_ERR(svn_cstring_atoi64(&dirent.size, size));
      else
        dirent.size = SVN_INVALID_FILESIZE;

      if (crev)
        SVN_ERR(svn_revnum_parse(&dirent.created_rev, crev, NULL));
      else
        dirent.created_rev = SVN_INVALID_REVNUM;

      if (date)
        SVN_ERR(svn_time_from_cstring(&dirent.time, date, scratch_pool));

      if (list_ctx->author)
        dirent.last_author = list_ctx->author;

      /* Invoke RECEIVER */
      SVN_ERR(list_ctx->receiver(dirent_path, &dirent,
                                 list_ctx->receiver_baton, scratch_pool));

      /* Reset buffered info. */
      list_ctx->author = NULL;
    }

  return SVN_NO_ERROR;
}