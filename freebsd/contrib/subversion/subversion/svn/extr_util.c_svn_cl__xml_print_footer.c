#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * svn_cl__error_checked_fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 

svn_error_t *
svn_cl__xml_print_footer(const char *tagname,
                         apr_pool_t *pool)
{
  svn_stringbuf_t *sb = svn_stringbuf_create_empty(pool);

  /* "</TAGNAME>" */
  svn_xml_make_close_tag(&sb, pool, tagname);
  return svn_cl__error_checked_fputs(sb->data, stdout);
}