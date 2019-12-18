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
typedef  enum svn_xml_open_tag_style { ____Placeholder_svn_xml_open_tag_style } svn_xml_open_tag_style ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_stringbuf_create_ensure (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_escape_attr_cstring (int /*<<< orphan*/ **,void*,int /*<<< orphan*/ *) ; 
 int svn_xml_protect_pcdata ; 
 int svn_xml_self_closing ; 

void
svn_xml_make_open_tag_hash(svn_stringbuf_t **str,
                           apr_pool_t *pool,
                           enum svn_xml_open_tag_style style,
                           const char *tagname,
                           apr_hash_t *attributes)
{
  apr_hash_index_t *hi;
  apr_size_t est_size = strlen(tagname) + 4 + apr_hash_count(attributes) * 30;

  if (*str == NULL)
    *str = svn_stringbuf_create_ensure(est_size, pool);

  svn_stringbuf_appendcstr(*str, "<");
  svn_stringbuf_appendcstr(*str, tagname);

  for (hi = apr_hash_first(pool, attributes); hi; hi = apr_hash_next(hi))
    {
      const void *key;
      void *val;

      apr_hash_this(hi, &key, NULL, &val);
      assert(val != NULL);

      svn_stringbuf_appendcstr(*str, "\n   ");
      svn_stringbuf_appendcstr(*str, key);
      svn_stringbuf_appendcstr(*str, "=\"");
      svn_xml_escape_attr_cstring(str, val, pool);
      svn_stringbuf_appendcstr(*str, "\"");
    }

  if (style == svn_xml_self_closing)
    svn_stringbuf_appendcstr(*str, "/");
  svn_stringbuf_appendcstr(*str, ">");
  if (style != svn_xml_protect_pcdata)
    svn_stringbuf_appendcstr(*str, "\n");
}