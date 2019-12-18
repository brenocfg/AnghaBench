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
struct adreq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * adh_remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIST_CMD_KEEPALIVE ; 
 int /*<<< orphan*/  QUEUE_INSERT (struct adreq*,int /*<<< orphan*/ *) ; 
 struct adreq* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct adreq*,int /*<<< orphan*/ ) ; 
 TYPE_1__* adhost ; 
 int /*<<< orphan*/  adist_free_list ; 
 int /*<<< orphan*/  adist_free_list_lock ; 
 int /*<<< orphan*/  adist_remote_lock ; 
 int /*<<< orphan*/  adist_send_list ; 
 int /*<<< orphan*/  adr_next ; 
 int /*<<< orphan*/  adreq_fill (struct adreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*) ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
keepalive_send(void)
{
	struct adreq *adreq;

	rw_rlock(&adist_remote_lock);
	if (adhost->adh_remote == NULL) {
		rw_unlock(&adist_remote_lock);
		return;
	}
	rw_unlock(&adist_remote_lock);

	mtx_lock(&adist_free_list_lock);
	adreq = TAILQ_FIRST(&adist_free_list);
	if (adreq != NULL)
		TAILQ_REMOVE(&adist_free_list, adreq, adr_next);
	mtx_unlock(&adist_free_list_lock);
	if (adreq == NULL)
		return;

	adreq_fill(adreq, ADIST_CMD_KEEPALIVE, NULL, 0);

	QUEUE_INSERT(adreq, &adist_send_list);

	pjdlog_debug(3, "keepalive_send: Request sent.");
}