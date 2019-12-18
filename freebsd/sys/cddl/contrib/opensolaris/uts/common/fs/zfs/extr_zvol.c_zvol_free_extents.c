#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zv_extents; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  int /*<<< orphan*/  zvol_extent_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zvol_free_extents(zvol_state_t *zv)
{
	zvol_extent_t *ze;

	while (ze = list_head(&zv->zv_extents)) {
		list_remove(&zv->zv_extents, ze);
		kmem_free(ze, sizeof (zvol_extent_t));
	}
}