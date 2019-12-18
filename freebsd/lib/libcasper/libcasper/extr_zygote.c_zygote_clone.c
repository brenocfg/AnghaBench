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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int ENXIO ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_exists_number (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 int nvlist_take_descriptor (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * nvlist_xfer (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zygote_sock ; 

int
zygote_clone(uint64_t funcidx, int *chanfdp, int *procfdp)
{
	nvlist_t *nvl;
	int error;

	if (zygote_sock == -1) {
		/* Zygote didn't start. */
		errno = ENXIO;
		return (-1);
	}

	nvl = nvlist_create(0);
	nvlist_add_number(nvl, "funcidx", funcidx);
	nvl = nvlist_xfer(zygote_sock, nvl, 0);
	if (nvl == NULL)
		return (-1);
	if (nvlist_exists_number(nvl, "error")) {
		error = (int)nvlist_get_number(nvl, "error");
		nvlist_destroy(nvl);
		errno = error;
		return (-1);
	}

	*chanfdp = nvlist_take_descriptor(nvl, "chanfd");
	*procfdp = nvlist_take_descriptor(nvl, "procfd");

	nvlist_destroy(nvl);
	return (0);
}