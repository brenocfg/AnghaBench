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
#define  CTRL_DIR_FORCE_BOTH 129 
#define  CTRL_DIR_IN_OR_BOTH 128 

__attribute__((used)) static inline const char * ctrl_dir_state_txt(int s)
{
	switch (s) {
	case CTRL_DIR_FORCE_BOTH: return "FORCE_BOTH";
	case CTRL_DIR_IN_OR_BOTH: return "IN_OR_BOTH";
	default: return "Unknown";
	}
}