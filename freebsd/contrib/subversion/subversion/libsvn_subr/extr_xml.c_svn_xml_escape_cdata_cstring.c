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
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  xml_escape_cdata (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
svn_xml_escape_cdata_cstring(svn_stringbuf_t **outstr,
                             const char *string,
                             apr_pool_t *pool)
{
  xml_escape_cdata(outstr, string, (apr_size_t) strlen(string), pool);
}