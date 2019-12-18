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
typedef  int /*<<< orphan*/  svn_config__open_section_fn ;
struct TYPE_4__ {int /*<<< orphan*/  add_value; int /*<<< orphan*/  close_section; int /*<<< orphan*/  open_section; } ;
typedef  TYPE_1__ svn_config__constructor_t ;
typedef  int /*<<< orphan*/  svn_config__close_section_fn ;
typedef  int /*<<< orphan*/  svn_config__add_value_fn ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_config__constructor_t *
svn_config__constructor_create(
    svn_config__open_section_fn open_section_callback,
    svn_config__close_section_fn close_section_callback,
    svn_config__add_value_fn add_value_callback,
    apr_pool_t *result_pool)
{
  svn_config__constructor_t *ctor = apr_palloc(result_pool, sizeof(*ctor));
  ctor->open_section = open_section_callback;
  ctor->close_section = close_section_callback;
  ctor->add_value = add_value_callback;
  return ctor;
}