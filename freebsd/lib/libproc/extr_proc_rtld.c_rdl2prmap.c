#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rdl_prot; int /*<<< orphan*/  rdl_path; int /*<<< orphan*/  rdl_offset; scalar_t__ rdl_saddr; scalar_t__ rdl_eaddr; } ;
typedef  TYPE_1__ rd_loadobj_t ;
struct TYPE_6__ {int /*<<< orphan*/  pr_mapname; int /*<<< orphan*/  pr_mflags; int /*<<< orphan*/  pr_offset; scalar_t__ pr_size; scalar_t__ pr_vaddr; } ;
typedef  TYPE_2__ prmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_EXEC ; 
 int /*<<< orphan*/  MA_READ ; 
 int /*<<< orphan*/  MA_WRITE ; 
 int RD_RDL_R ; 
 int RD_RDL_W ; 
 int RD_RDL_X ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdl2prmap(const rd_loadobj_t *rdl, prmap_t *map)
{

	map->pr_vaddr = rdl->rdl_saddr;
	map->pr_size = rdl->rdl_eaddr - rdl->rdl_saddr;
	map->pr_offset = rdl->rdl_offset;
	map->pr_mflags = 0;
	if (rdl->rdl_prot & RD_RDL_R)
		map->pr_mflags |= MA_READ;
	if (rdl->rdl_prot & RD_RDL_W)
		map->pr_mflags |= MA_WRITE;
	if (rdl->rdl_prot & RD_RDL_X)
		map->pr_mflags |= MA_EXEC;
	(void)strlcpy(map->pr_mapname, rdl->rdl_path,
	    sizeof(map->pr_mapname));
}