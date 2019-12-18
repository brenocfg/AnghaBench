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
struct TYPE_4__ {void* props_modified; void* text_modified; } ;
typedef  TYPE_1__ svn_log_changed_path2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* svn_tristate_unknown ; 

svn_log_changed_path2_t *
svn_log_changed_path2_create(apr_pool_t *pool)
{
  svn_log_changed_path2_t *new_changed_path
    = apr_pcalloc(pool, sizeof(*new_changed_path));

  new_changed_path->text_modified = svn_tristate_unknown;
  new_changed_path->props_modified = svn_tristate_unknown;

  return new_changed_path;
}