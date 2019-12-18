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
struct atmif_reg {int /*<<< orphan*/  notify; int /*<<< orphan*/ * ifpreg; } ;
struct atmif_priv {int /*<<< orphan*/  notify; int /*<<< orphan*/ * ifpreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMIF_NOTIFY_DESTROY ; 
 struct atmif_reg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct atmif_reg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmif_list ; 
 int /*<<< orphan*/  atmif_send_notification (struct atmif_reg*,int /*<<< orphan*/ ,uintptr_t) ; 
 int /*<<< orphan*/  atmif_sys_destroy (struct atmif_reg*) ; 
 int /*<<< orphan*/  free (struct atmif_reg*) ; 
 int /*<<< orphan*/  last_change ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mibif_unnotify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_tick ; 

__attribute__((used)) static void
atmif_destroy(struct atmif_priv *aif)
{
	struct atmif_reg *r0;

	atmif_send_notification(aif, ATMIF_NOTIFY_DESTROY,
	    (uintptr_t)0);

	atmif_sys_destroy(aif);

	if (aif->ifpreg != NULL)
		mibif_unnotify(aif->ifpreg);

	while ((r0 = TAILQ_FIRST(&aif->notify)) != NULL) {
		TAILQ_REMOVE(&aif->notify, r0, link);
		free(r0);
	}

	TAILQ_REMOVE(&atmif_list, aif, link);
	free(aif);

	last_change = this_tick;
}