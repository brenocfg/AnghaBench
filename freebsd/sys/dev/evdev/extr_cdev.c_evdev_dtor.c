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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct evdev_client {int /*<<< orphan*/  ec_buffer_mtx; int /*<<< orphan*/  ec_sigio; TYPE_1__ ec_selp; int /*<<< orphan*/  ec_evdev; int /*<<< orphan*/  ec_revoked; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVDEV_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_EVDEV ; 
 int /*<<< orphan*/  evdev_dispose_client (int /*<<< orphan*/ ,struct evdev_client*) ; 
 int /*<<< orphan*/  free (struct evdev_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 

__attribute__((used)) static void
evdev_dtor(void *data)
{
	struct evdev_client *client = (struct evdev_client *)data;

	EVDEV_LOCK(client->ec_evdev);
	if (!client->ec_revoked)
		evdev_dispose_client(client->ec_evdev, client);
	EVDEV_UNLOCK(client->ec_evdev);

	knlist_clear(&client->ec_selp.si_note, 0);
	seldrain(&client->ec_selp);
	knlist_destroy(&client->ec_selp.si_note);
	funsetown(&client->ec_sigio);
	mtx_destroy(&client->ec_buffer_mtx);
	free(client, M_EVDEV);
}