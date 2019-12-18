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
struct ch_reg {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_GET_QSET_NUM ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_reg*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
qset_num_config(int argc, char *argv[], int start_arg, const char *iff_name)
{
	struct ch_reg reg;

	(void) argv;

	if (argc == start_arg) {
		if (doit(iff_name, CHELSIO_GET_QSET_NUM, &reg) < 0)
			err(1, "get qsets");
		printf("%u\n", reg.val);
		return 0;
	}

	return -1;
}