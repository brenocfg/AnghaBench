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

__attribute__((used)) static inline bool num_vfs_valid(int num_vfs)
{
	bool valid = false;

	switch (num_vfs) {
	case 16:
	case 32:
	case 64:
	case 128:
		valid = true;
		break;
	}

	return valid;
}