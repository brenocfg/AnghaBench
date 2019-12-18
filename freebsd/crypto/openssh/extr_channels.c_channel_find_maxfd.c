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
typedef  size_t u_int ;
struct ssh_channels {size_t channels_alloc; int channel_max_fd; TYPE_1__** channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  efd; int /*<<< orphan*/  wfd; int /*<<< orphan*/  rfd; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int MAXIMUM (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
channel_find_maxfd(struct ssh_channels *sc)
{
	u_int i;
	int max = 0;
	Channel *c;

	for (i = 0; i < sc->channels_alloc; i++) {
		c = sc->channels[i];
		if (c != NULL) {
			max = MAXIMUM(max, c->rfd);
			max = MAXIMUM(max, c->wfd);
			max = MAXIMUM(max, c->efd);
		}
	}
	sc->channel_max_fd = max;
}