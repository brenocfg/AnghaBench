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
typedef  int /*<<< orphan*/  value_t ;

/* Variables and functions */
 int /*<<< orphan*/ * M_values ; 

__attribute__((used)) inline static value_t metafile_get_value (int temp_id) {
  return M_values ? M_values[temp_id] : 0;
}