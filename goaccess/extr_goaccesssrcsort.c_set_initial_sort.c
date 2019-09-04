#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int field; int sort; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_sort_module (int,int) ; 
 int get_module_enum (char const*) ; 
 int get_sort_field_enum (char const*) ; 
 int get_sort_order_enum (char const*) ; 
 TYPE_1__* module_sort ; 

void
set_initial_sort (const char *smod, const char *sfield, const char *ssort)
{
  int module, field, order;
  if ((module = get_module_enum (smod)) == -1)
    return;

  if ((field = get_sort_field_enum (sfield)) == -1)
    return;
  if ((order = get_sort_order_enum (ssort)) == -1)
    return;
  if (!can_sort_module (module, field))
    return;

  module_sort[module].field = field;
  module_sort[module].sort = order;
}