#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* connect_path; struct TYPE_5__* connect_host; struct TYPE_5__* listen_path; struct TYPE_5__* listen_host; } ;
struct TYPE_4__ {int num_local_forwards; int num_remote_forwards; int /*<<< orphan*/  tun_open; TYPE_2__* remote_forwards; TYPE_2__* local_forwards; } ;
typedef  TYPE_1__ Options ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_TUNMODE_NO ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void
clear_forwardings(Options *options)
{
	int i;

	for (i = 0; i < options->num_local_forwards; i++) {
		free(options->local_forwards[i].listen_host);
		free(options->local_forwards[i].listen_path);
		free(options->local_forwards[i].connect_host);
		free(options->local_forwards[i].connect_path);
	}
	if (options->num_local_forwards > 0) {
		free(options->local_forwards);
		options->local_forwards = NULL;
	}
	options->num_local_forwards = 0;
	for (i = 0; i < options->num_remote_forwards; i++) {
		free(options->remote_forwards[i].listen_host);
		free(options->remote_forwards[i].listen_path);
		free(options->remote_forwards[i].connect_host);
		free(options->remote_forwards[i].connect_path);
	}
	if (options->num_remote_forwards > 0) {
		free(options->remote_forwards);
		options->remote_forwards = NULL;
	}
	options->num_remote_forwards = 0;
	options->tun_open = SSH_TUNMODE_NO;
}