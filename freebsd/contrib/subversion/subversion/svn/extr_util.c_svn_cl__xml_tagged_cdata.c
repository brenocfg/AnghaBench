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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  svn_xml_escape_cdata_cstring (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_protect_pcdata ; 

void
svn_cl__xml_tagged_cdata(svn_stringbuf_t **sb,
                         apr_pool_t *pool,
                         const char *tagname,
                         const char *string)
{
  if (string)
    {
      svn_xml_make_open_tag(sb, pool, svn_xml_protect_pcdata,
                            tagname, SVN_VA_NULL);
      svn_xml_escape_cdata_cstring(sb, string, pool);
      svn_xml_make_close_tag(sb, pool, tagname);
    }
}