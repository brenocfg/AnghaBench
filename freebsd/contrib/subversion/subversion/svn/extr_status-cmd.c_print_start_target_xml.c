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
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * svn_cl__error_checked_fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_normal ; 

__attribute__((used)) static svn_error_t *
print_start_target_xml(const char *target, apr_pool_t *pool)
{
  svn_stringbuf_t *sb = svn_stringbuf_create_empty(pool);

  svn_xml_make_open_tag(&sb, pool, svn_xml_normal, "target",
                        "path", target, SVN_VA_NULL);

  return svn_cl__error_checked_fputs(sb->data, stdout);
}