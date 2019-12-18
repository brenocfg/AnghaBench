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
struct ecore_queue_update_params {int /*<<< orphan*/  update_flags; } ;
struct TYPE_2__ {struct ecore_queue_update_params update; } ;
struct ecore_queue_state_params {TYPE_1__ params; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MEMSET (struct ecore_queue_update_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ECORE_Q_UPDATE_ACTIVATE ; 
 int /*<<< orphan*/  ECORE_Q_UPDATE_ACTIVATE_CHNG ; 
 int /*<<< orphan*/  ECORE_SET_BIT_NA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_q_send_update (struct bxe_softc*,struct ecore_queue_state_params*) ; 

__attribute__((used)) static inline int ecore_q_send_activate(struct bxe_softc *sc,
					struct ecore_queue_state_params *params)
{
	struct ecore_queue_update_params *update = &params->params.update;

	ECORE_MEMSET(update, 0, sizeof(*update));

	ECORE_SET_BIT_NA(ECORE_Q_UPDATE_ACTIVATE, &update->update_flags);
	ECORE_SET_BIT_NA(ECORE_Q_UPDATE_ACTIVATE_CHNG, &update->update_flags);

	return ecore_q_send_update(sc, params);
}