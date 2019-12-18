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
 int /*<<< orphan*/  IB_SMI_CLASS ; 
 int /*<<< orphan*/  IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  dump_char ; 
 int /*<<< orphan*/  mgmt_class ; 

__attribute__((used)) static int process_opt(void *context, int ch, char *optarg)
{
	switch (ch) {
	case 's':
		dump_char++;
		break;
	case 'D':
		mgmt_class = IB_SMI_DIRECT_CLASS;
		break;
	case 'L':
		mgmt_class = IB_SMI_CLASS;
		break;
	default:
		return -1;
	}
	return 0;
}