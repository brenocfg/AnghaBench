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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fast_classifier_close () ; 
 scalar_t__ fast_classifier_init () ; 
 int /*<<< orphan*/  fast_classifier_ipv4_offload (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fast_classifier_listen_for_messages () ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char *argv[])
{
	if (fast_classifier_init() < 0) {
		printf("Unable to init generic netlink\n");
		exit(1);
	}

	fast_classifier_ipv4_offload('a', 0, 0, 0, 0);

	/* this never returns */
	fast_classifier_listen_for_messages();

	fast_classifier_close();

	return 0;
}