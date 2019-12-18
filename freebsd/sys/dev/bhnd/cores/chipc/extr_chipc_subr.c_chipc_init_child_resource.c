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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  uintptr_t bhnd_size_t ;

/* Variables and functions */
 int bus_space_subregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 scalar_t__ rman_get_virtual (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_virtual (struct resource*,void*) ; 

int
chipc_init_child_resource(struct resource *r,
    struct resource *parent, bhnd_size_t offset, bhnd_size_t size)
{
	bus_space_handle_t	bh, child_bh;
	bus_space_tag_t		bt;
	uintptr_t		vaddr;
	int			error;

	/* Fetch the parent resource's bus values */
	vaddr = (uintptr_t) rman_get_virtual(parent);
	bt = rman_get_bustag(parent);
	bh = rman_get_bushandle(parent);

	/* Configure child resource with offset-adjusted values */
	vaddr += offset;
	error = bus_space_subregion(bt, bh, offset, size, &child_bh);
	if (error)
		return (error);

	rman_set_virtual(r, (void *) vaddr);
	rman_set_bustag(r, bt);
	rman_set_bushandle(r, child_bh);

	return (0);
}