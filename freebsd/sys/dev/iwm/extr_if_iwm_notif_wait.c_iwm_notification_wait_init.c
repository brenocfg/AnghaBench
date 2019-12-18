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
struct iwm_softc {int dummy; } ;
struct iwm_notif_wait_data {struct iwm_softc* sc; int /*<<< orphan*/  list; int /*<<< orphan*/  lk_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_WAIT_LOCK_INIT (struct iwm_notif_wait_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct iwm_notif_wait_data* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

struct iwm_notif_wait_data *
iwm_notification_wait_init(struct iwm_softc *sc)
{
	struct iwm_notif_wait_data *data;

	data = malloc(sizeof(*data), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (data != NULL) {
		snprintf(data->lk_buf, 32, "iwm wait_notif");
		IWM_WAIT_LOCK_INIT(data, data->lk_buf);
		STAILQ_INIT(&data->list);
		data->sc = sc;
	}

	return data;
}