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

/* Variables and functions */
 scalar_t__ MAX_VARS ; 
 scalar_t__ __vars ; 
 scalar_t__ last_var_ptr ; 

void tl_parse_on_rinit (void) {
  last_var_ptr = __vars + MAX_VARS;
}