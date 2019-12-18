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
typedef  int /*<<< orphan*/ * uint64_t ;
struct modrm {int reg; int base; int /*<<< orphan*/ * offset; int /*<<< orphan*/  type; } ;
struct gen_state {int dummy; } ;
typedef  int /*<<< orphan*/ * gadget_t ;
typedef  enum arg { ____Placeholder_arg } arg ;
typedef  int /*<<< orphan*/ * dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  GEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNDEFINED ; 
#define  arg_1 131 
 int arg_addr ; 
 int arg_count ; 
 int arg_imm ; 
 int arg_mem ; 
#define  arg_mem_addr 130 
#define  arg_modrm_reg 129 
#define  arg_modrm_val 128 
 int arg_reg_a ; 
 int /*<<< orphan*/  gen_addr (struct gen_state*,struct modrm*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modrm_mem ; 
 int /*<<< orphan*/  modrm_reg ; 
 int reg_none ; 
 int sz (int) ; 

__attribute__((used)) static inline bool gen_op(struct gen_state *state, gadget_t *gadgets, enum arg arg, struct modrm *modrm, uint64_t *imm, int size, dword_t saved_ip, bool seg_gs, dword_t addr_offset) {
    size = sz(size);
    gadgets = gadgets + size * arg_count;

    switch (arg) {
        case arg_modrm_reg:
            // TODO find some way to assert that this won't overflow?
            arg = modrm->reg + arg_reg_a; break;
        case arg_modrm_val:
            if (modrm->type == modrm_reg)
                arg = modrm->base + arg_reg_a;
            else
                arg = arg_mem;
            break;
        case arg_mem_addr:
            arg = arg_mem;
            modrm->type = modrm_mem;
            modrm->base = reg_none;
            modrm->offset = addr_offset;
            break;
        case arg_1:
            arg = arg_imm;
            *imm = 1;
            break;
    }
    if (arg >= arg_count || gadgets[arg] == NULL) {
        UNDEFINED;
    }
    if (arg == arg_mem || arg == arg_addr) {
        if (!gen_addr(state, modrm, seg_gs, saved_ip))
            return false;
    }
    GEN(gadgets[arg]);
    if (arg == arg_imm)
        GEN(*imm);
    else if (arg == arg_mem)
        GEN(saved_ip);
    return true;
}