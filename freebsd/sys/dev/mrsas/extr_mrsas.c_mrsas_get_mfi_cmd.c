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
struct mrsas_softc {int /*<<< orphan*/  mfi_cmd_pool_lock; int /*<<< orphan*/  mrsas_mfi_cmd_list_head; } ;
struct mrsas_mfi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct mrsas_mfi_cmd* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mrsas_mfi_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 

struct mrsas_mfi_cmd *
mrsas_get_mfi_cmd(struct mrsas_softc *sc)
{
	struct mrsas_mfi_cmd *cmd = NULL;

	mtx_lock(&sc->mfi_cmd_pool_lock);
	if (!TAILQ_EMPTY(&sc->mrsas_mfi_cmd_list_head)) {
		cmd = TAILQ_FIRST(&sc->mrsas_mfi_cmd_list_head);
		TAILQ_REMOVE(&sc->mrsas_mfi_cmd_list_head, cmd, next);
	}
	mtx_unlock(&sc->mfi_cmd_pool_lock);

	return cmd;
}