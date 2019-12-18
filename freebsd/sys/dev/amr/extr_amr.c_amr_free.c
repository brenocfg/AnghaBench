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
struct cdev {int dummy; } ;
struct amr_softc {int /*<<< orphan*/  amr_list_lock; int /*<<< orphan*/  amr_hw_lock; struct cdev* amr_dev_t; int /*<<< orphan*/  amr_cmd_clusters; int /*<<< orphan*/ * amr_pass; int /*<<< orphan*/  amr_dev; } ;
struct amr_command_cluster {int dummy; } ;

/* Variables and functions */
 struct amr_command_cluster* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct amr_command_cluster*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acc_link ; 
 int /*<<< orphan*/  amr_freecmd_cluster (struct amr_command_cluster*) ; 
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 

void
amr_free(struct amr_softc *sc)
{
    struct amr_command_cluster	*acc;

    /* detach from CAM */
    if (sc->amr_pass != NULL)
	device_delete_child(sc->amr_dev, sc->amr_pass);

    /* throw away any command buffers */
    while ((acc = TAILQ_FIRST(&sc->amr_cmd_clusters)) != NULL) {
	TAILQ_REMOVE(&sc->amr_cmd_clusters, acc, acc_link);
	amr_freecmd_cluster(acc);
    }

    /* destroy control device */
    if( sc->amr_dev_t != (struct cdev *)NULL)
	    destroy_dev(sc->amr_dev_t);

    if (mtx_initialized(&sc->amr_hw_lock))
	mtx_destroy(&sc->amr_hw_lock);

    if (mtx_initialized(&sc->amr_list_lock))
	mtx_destroy(&sc->amr_list_lock);
}