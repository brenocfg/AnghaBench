#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ summarize_kind; int /*<<< orphan*/  node_kind; scalar_t__ prop_changed; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ svn_client_diff_summarize_t ;
struct summarize_baton_t {char* anchor; scalar_t__ ignore_properties; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  kind_to_word (scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * svn_cl__error_checked_fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cl__node_kind_str_xml (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_client_diff_summarize_kind_normal ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 char* svn_path_url_add_component2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_escape_cdata_cstring (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (TYPE_1__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_protect_pcdata ; 

__attribute__((used)) static svn_error_t *
summarize_xml(const svn_client_diff_summarize_t *summary,
              void *baton,
              apr_pool_t *pool)
{
  struct summarize_baton_t *b = baton;
  /* Full path to the object being diffed.  This is created by taking the
   * baton, and appending the target's relative path. */
  const char *path = b->anchor;
  svn_stringbuf_t *sb = svn_stringbuf_create_empty(pool);
  const char *prop_change;

  if (b->ignore_properties &&
      summary->summarize_kind == svn_client_diff_summarize_kind_normal)
    return SVN_NO_ERROR;

  /* Tack on the target path, so we can differentiate between different parts
   * of the output when we're given multiple targets. */
  if (svn_path_is_url(path))
    {
      path = svn_path_url_add_component2(path, summary->path, pool);
    }
  else
    {
      path = svn_dirent_join(path, summary->path, pool);

      /* Convert non-urls to local style, so that things like ""
         show up as "." */
      path = svn_dirent_local_style(path, pool);
    }

  prop_change = summary->prop_changed ? "modified" : "none";
  if (b->ignore_properties)
    prop_change = "none";

  svn_xml_make_open_tag(&sb, pool, svn_xml_protect_pcdata, "path",
                        "kind", svn_cl__node_kind_str_xml(summary->node_kind),
                        "item", kind_to_word(summary->summarize_kind),
                        "props",  prop_change,
                        SVN_VA_NULL);

  svn_xml_escape_cdata_cstring(&sb, path, pool);
  svn_xml_make_close_tag(&sb, pool, "path");

  return svn_cl__error_checked_fputs(sb->data, stdout);
}