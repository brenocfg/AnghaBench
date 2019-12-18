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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  enum svn_xml_open_tag_style { ____Placeholder_svn_xml_open_tag_style } svn_xml_open_tag_style ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_xml_ap_to_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag_hash (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ *) ; 

void
svn_xml_make_open_tag_v(svn_stringbuf_t **str,
                        apr_pool_t *pool,
                        enum svn_xml_open_tag_style style,
                        const char *tagname,
                        va_list ap)
{
  apr_pool_t *subpool = svn_pool_create(pool);
  apr_hash_t *ht = svn_xml_ap_to_hash(ap, subpool);

  svn_xml_make_open_tag_hash(str, pool, style, tagname, ht);
  svn_pool_destroy(subpool);
}