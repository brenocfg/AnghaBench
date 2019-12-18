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
struct ntb_child {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  dev; struct ntb_child* next; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ntb_child** device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ntb_child*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_destroy (int /*<<< orphan*/ *) ; 

int
ntb_unregister_device(device_t dev)
{
	struct ntb_child **cpp = device_get_softc(dev);
	struct ntb_child *nc;
	int error = 0;

	while ((nc = *cpp) != NULL) {
		*cpp = (*cpp)->next;
		error = device_delete_child(dev, nc->dev);
		if (error)
			break;
		rm_destroy(&nc->ctx_lock);
		free(nc, M_DEVBUF);
	}
	return (error);
}