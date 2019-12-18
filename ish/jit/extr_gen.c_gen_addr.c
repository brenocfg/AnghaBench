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
struct modrm {scalar_t__ base; scalar_t__ type; int index; scalar_t__ shift; int /*<<< orphan*/  offset; } ;
struct gen_state {int dummy; } ;
typedef  int /*<<< orphan*/  dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  addr ; 
 int /*<<< orphan*/  addr_none ; 
 int /*<<< orphan*/  g (int) ; 
 int /*<<< orphan*/  ga (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ modrm_mem_si ; 
 scalar_t__ reg_none ; 
 int /*<<< orphan*/  si ; 

bool gen_addr(struct gen_state *state, struct modrm *modrm, bool seg_gs, dword_t saved_ip) {
    if (modrm->base == reg_none)
        gg(addr_none, modrm->offset);
    else
        gag(addr, modrm->base, modrm->offset);
    if (modrm->type == modrm_mem_si)
        ga(si, modrm->index * 4 + modrm->shift);
    if (seg_gs)
        g(seg_gs);
    return true;
}