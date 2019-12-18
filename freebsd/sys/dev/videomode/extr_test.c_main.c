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
struct TYPE_2__ {int dot_clock; int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int videomode_count ; 
 TYPE_1__* videomode_list ; 

int
main(int argc, char **argv)
{
	int	i, j;

	for (i = 1; i < argc ; i++) {
		for (j = 0; j < videomode_count; j++) {
			if (strcmp(videomode_list[j].name, argv[i]) == 0) {
				printf("dotclock for mode %s = %d, flags %x\n",
				    argv[i],
				    videomode_list[j].dot_clock,
				    videomode_list[j].flags);
				break;
			}
		}
		if (j == videomode_count) {
			printf("dotclock for mode %s not found\n", argv[i]);
		}
	}
}