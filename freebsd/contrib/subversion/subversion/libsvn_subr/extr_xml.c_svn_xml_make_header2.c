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
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

void
svn_xml_make_header2(svn_stringbuf_t **str, const char *encoding,
                     apr_pool_t *pool)
{

  if (*str == NULL)
    *str = svn_stringbuf_create_empty(pool);
  svn_stringbuf_appendcstr(*str, "<?xml version=\"1.0\"");
  if (encoding)
    {
      encoding = apr_psprintf(pool, " encoding=\"%s\"", encoding);
      svn_stringbuf_appendcstr(*str, encoding);
    }
  svn_stringbuf_appendcstr(*str, "?>\n");
}