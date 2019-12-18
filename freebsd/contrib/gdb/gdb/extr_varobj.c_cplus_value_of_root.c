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
struct varobj {int dummy; } ;
struct value {int dummy; } ;

/* Variables and functions */
 struct value* c_value_of_root (struct varobj**) ; 

__attribute__((used)) static struct value *
cplus_value_of_root (struct varobj **var_handle)
{
  return c_value_of_root (var_handle);
}