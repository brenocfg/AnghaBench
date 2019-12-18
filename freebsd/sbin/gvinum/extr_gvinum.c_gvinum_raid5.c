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
 int /*<<< orphan*/  create_volume (int,char* const*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
gvinum_raid5(int argc, char * const *argv)
{

	if (argc < 2) {
		warnx("usage:\traid5 [-fv] [-s stripesize] [-n name] drives\n");
		return;
	}
	create_volume(argc, argv, "raid5");
}