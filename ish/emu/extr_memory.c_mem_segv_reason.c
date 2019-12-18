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
struct pt_entry {int flags; } ;
struct mem {int dummy; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int MEM_READ ; 
 int MEM_WRITE ; 
 int /*<<< orphan*/  PAGE (int /*<<< orphan*/ ) ; 
 int P_READ ; 
 int P_WRITE ; 
 int SEGV_ACCERR_ ; 
 int SEGV_MAPERR_ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct pt_entry* mem_pt (struct mem*,int /*<<< orphan*/ ) ; 

int mem_segv_reason(struct mem *mem, addr_t addr, int type) {
    assert(type == MEM_READ || type == MEM_WRITE);
    struct pt_entry *pt = mem_pt(mem, PAGE(addr));
    if (pt == NULL)
        return SEGV_MAPERR_;
    if ((type == MEM_READ && !(pt->flags & P_READ)) ||
            (type == MEM_WRITE && !(pt->flags & P_WRITE)))
        return SEGV_ACCERR_;
    die("caught segv for valid access");
}