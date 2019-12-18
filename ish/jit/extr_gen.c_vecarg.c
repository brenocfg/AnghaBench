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
struct modrm {int /*<<< orphan*/  type; } ;
typedef  enum vec_arg { ____Placeholder_vec_arg } vec_arg ;
typedef  enum arg { ____Placeholder_arg } arg ;

/* Variables and functions */
#define  arg_imm 132 
#define  arg_modrm_reg 131 
#define  arg_modrm_val 130 
#define  arg_xmm_modrm_reg 129 
#define  arg_xmm_modrm_val 128 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  modrm_reg ; 
 int vec_arg_imm ; 
 int vec_arg_mem ; 
 int vec_arg_reg ; 
 int vec_arg_xmm ; 

__attribute__((used)) static inline enum vec_arg vecarg(enum arg arg, struct modrm *modrm) {
    switch (arg) {
        case arg_modrm_reg:
            return vec_arg_reg;
        case arg_imm:
            return vec_arg_imm;
        case arg_xmm_modrm_reg:
            return vec_arg_xmm;
        case arg_modrm_val:
            if (modrm->type == modrm_reg)
                return vec_arg_reg;
            return vec_arg_mem;
        case arg_xmm_modrm_val:
            if (modrm->type == modrm_reg)
                return vec_arg_xmm;
            return vec_arg_mem;
        default:
            die("unimplemented vecarg");
    }
}