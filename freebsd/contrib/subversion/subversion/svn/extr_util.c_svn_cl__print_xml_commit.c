#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cl__xml_tagged_cdata (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_normal ; 

void
svn_cl__print_xml_commit(svn_stringbuf_t **sb,
                         svn_revnum_t revision,
                         const char *author,
                         const char *date,
                         apr_pool_t *pool)
{
  /* "<commit ...>" */
  svn_xml_make_open_tag(sb, pool, svn_xml_normal, "commit",
                        "revision",
                        apr_psprintf(pool, "%ld", revision), SVN_VA_NULL);

  /* "<author>xx</author>" */
  if (author)
    svn_cl__xml_tagged_cdata(sb, pool, "author", author);

  /* "<date>xx</date>" */
  if (date)
    svn_cl__xml_tagged_cdata(sb, pool, "date", date);

  /* "</commit>" */
  svn_xml_make_close_tag(sb, pool, "commit");
}