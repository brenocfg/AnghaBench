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
struct proc_handle {scalar_t__ status; int maparrsz; int /*<<< orphan*/ * rdap; int /*<<< orphan*/ * mappings; } ;
typedef  int /*<<< orphan*/  rd_agent_t ;

/* Variables and functions */
 scalar_t__ PS_IDLE ; 
 scalar_t__ PS_UNDEAD ; 
 scalar_t__ RD_OK ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  map_iter ; 
 scalar_t__ rd_loadobj_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct proc_handle*) ; 
 int /*<<< orphan*/ * rd_new (struct proc_handle*) ; 

rd_agent_t *
proc_rdagent(struct proc_handle *phdl)
{

	if (phdl->rdap == NULL && phdl->status != PS_UNDEAD &&
	    phdl->status != PS_IDLE) {
		if ((phdl->rdap = rd_new(phdl)) == NULL)
			return (NULL);

		phdl->maparrsz = 64;
		phdl->mappings = calloc(phdl->maparrsz,
		    sizeof(*phdl->mappings));
		if (phdl->mappings == NULL)
			return (phdl->rdap);
		if (rd_loadobj_iter(phdl->rdap, map_iter, phdl) != RD_OK)
			return (NULL);
	}
	return (phdl->rdap);
}