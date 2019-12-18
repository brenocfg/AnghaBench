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
struct nl_classifier_instance {int /*<<< orphan*/ * sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nl_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_socket_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void nl_classifier_exit(struct nl_classifier_instance *inst)
{
	if (inst->sock) {
		nl_close(inst->sock);
		nl_socket_free(inst->sock);
		inst->sock = NULL;
	}
	printf("nl classifier exit successful\n");
}