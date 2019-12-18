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
 int* M_flags ; 
 int* M_flags_small ; 

__attribute__((used)) inline static int metafile_get_flags (int temp_id) {
  return M_flags ? M_flags[temp_id] : M_flags_small[temp_id];
}