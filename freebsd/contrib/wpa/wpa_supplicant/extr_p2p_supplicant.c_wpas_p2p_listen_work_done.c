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
struct wpas_p2p_listen_work {int dummy; } ;
struct wpa_supplicant {TYPE_1__* p2p_listen_work; } ;
struct TYPE_2__ {struct wpas_p2p_listen_work* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  radio_work_done (TYPE_1__*) ; 
 int /*<<< orphan*/  wpas_p2p_listen_work_free (struct wpas_p2p_listen_work*) ; 

__attribute__((used)) static void wpas_p2p_listen_work_done(struct wpa_supplicant *wpa_s)
{
	struct wpas_p2p_listen_work *lwork;

	if (!wpa_s->p2p_listen_work)
		return;

	lwork = wpa_s->p2p_listen_work->ctx;
	wpas_p2p_listen_work_free(lwork);
	radio_work_done(wpa_s->p2p_listen_work);
	wpa_s->p2p_listen_work = NULL;
}