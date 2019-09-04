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
struct value_data {int /*<<< orphan*/  fields_mask; } ;

/* Variables and functions */
 int extra_mask_intcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct value_data*,int) ; 

void free_value_data (struct value_data *V) {
  zfree (V, 4 + 4 * extra_mask_intcount (V->fields_mask));
}