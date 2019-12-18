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
struct netmap_obj_pool {int _clustentries; int objtotal; scalar_t__ _clustsize; int /*<<< orphan*/  name; TYPE_1__* lut; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {char* vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nm_prdis (char*,int /*<<< orphan*/ ,scalar_t__,int,void const*) ; 
 int /*<<< orphan*/  nm_prerr (char*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
netmap_obj_offset(struct netmap_obj_pool *p, const void *vaddr)
{
	int i, k = p->_clustentries, n = p->objtotal;
	ssize_t ofs = 0;

	for (i = 0; i < n; i += k, ofs += p->_clustsize) {
		const char *base = p->lut[i].vaddr;
		ssize_t relofs = (const char *) vaddr - base;

		if (relofs < 0 || relofs >= p->_clustsize)
			continue;

		ofs = ofs + relofs;
		nm_prdis("%s: return offset %d (cluster %d) for pointer %p",
		    p->name, ofs, i, vaddr);
		return ofs;
	}
	nm_prerr("address %p is not contained inside any cluster (%s)",
	    vaddr, p->name);
	return 0; /* An error occurred */
}