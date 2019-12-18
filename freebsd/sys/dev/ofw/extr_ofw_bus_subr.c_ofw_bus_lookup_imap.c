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
typedef  int /*<<< orphan*/  uint8_t ;
struct ofw_bus_iinfo {scalar_t__ opi_imapsz; int opi_addrc; int /*<<< orphan*/  opi_imapmsk; int /*<<< orphan*/  opi_imap; } ;
typedef  int phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OF_getencprop (int,char*,void*,int) ; 
 int ofw_bus_search_intrmap (void*,int,void*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,int*) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
ofw_bus_lookup_imap(phandle_t node, struct ofw_bus_iinfo *ii, void *reg,
    int regsz, void *pintr, int pintrsz, void *mintr, int mintrsz,
    phandle_t *iparent)
{
	uint8_t maskbuf[regsz + pintrsz];
	int rv;

	if (ii->opi_imapsz <= 0)
		return (0);
	KASSERT(regsz >= ii->opi_addrc,
	    ("ofw_bus_lookup_imap: register size too small: %d < %d",
		regsz, ii->opi_addrc));
	if (node != -1) {
		rv = OF_getencprop(node, "reg", reg, regsz);
		if (rv < regsz)
			panic("ofw_bus_lookup_imap: cannot get reg property");
	}
	return (ofw_bus_search_intrmap(pintr, pintrsz, reg, ii->opi_addrc,
	    ii->opi_imap, ii->opi_imapsz, ii->opi_imapmsk, maskbuf, mintr,
	    mintrsz, iparent));
}