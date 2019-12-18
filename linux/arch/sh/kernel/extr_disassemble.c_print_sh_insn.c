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
typedef  int u32 ;
typedef  int u16 ;
struct sh_opcode_info {int* nibbles; int* arg; scalar_t__ name; } ;

/* Variables and functions */
#define  A_BDISP12 188 
#define  A_BDISP8 187 
#define  A_DBR 186 
#define  A_DEC_M 185 
#define  A_DEC_N 184 
#define  A_DISP_GBR 183 
#define  A_DISP_PC 182 
#define  A_DISP_REG_M 181 
#define  A_DISP_REG_N 180 
 int A_END ; 
#define  A_GBR 179 
#define  A_IMM 178 
#define  A_INC_M 177 
#define  A_INC_N 176 
#define  A_IND_M 175 
#define  A_IND_N 174 
#define  A_IND_R0_REG_M 173 
#define  A_IND_R0_REG_N 172 
#define  A_MACH 171 
#define  A_MACL 170 
#define  A_PR 169 
#define  A_R0 168 
#define  A_R0_GBR 167 
#define  A_REG_B 166 
#define  A_REG_M 165 
#define  A_REG_N 164 
#define  A_SGR 163 
#define  A_SPC 162 
#define  A_SR 161 
#define  A_SSR 160 
#define  A_VBR 159 
#define  BRANCH_12 158 
#define  BRANCH_8 157 
#define  DISP_4 156 
#define  DISP_8 155 
#define  DX_REG_M 154 
#define  DX_REG_N 153 
#define  D_REG_M 152 
#define  D_REG_N 151 
#define  FD_REG_N 150 
#define  FPSCR_M 149 
#define  FPSCR_N 148 
#define  FPUL_M 147 
#define  FPUL_N 146 
#define  F_FR0 145 
#define  F_REG_M 144 
#define  F_REG_N 143 
#define  IMM_4 142 
#define  IMM_4BY2 141 
#define  IMM_4BY4 140 
#define  IMM_8 139 
#define  IMM_8BY2 138 
#define  IMM_8BY4 137 
#define  PCRELIMM_8BY2 136 
#define  PCRELIMM_8BY4 135 
#define  REG_B 134 
#define  REG_M 133 
#define  REG_N 132 
#define  REG_NM 131 
#define  V_REG_M 130 
#define  V_REG_N 129 
#define  XMTRX_M4 128 
 int /*<<< orphan*/  __get_user (int,int*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 struct sh_opcode_info* sh_table ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void print_sh_insn(u32 memaddr, u16 insn)
{
	int relmask = ~0;
	int nibs[4] = { (insn >> 12) & 0xf, (insn >> 8) & 0xf, (insn >> 4) & 0xf, insn & 0xf};
	int lastsp;
	struct sh_opcode_info *op = sh_table;

	for (; op->name; op++) {
		int n;
		int imm = 0;
		int rn = 0;
		int rm = 0;
		int rb = 0;
		int disp_pc;
		int disp_pc_addr = 0;

		for (n = 0; n < 4; n++) {
			int i = op->nibbles[n];

			if (i < 16) {
				if (nibs[n] == i)
					continue;
				goto fail;
			}
			switch (i) {
			case BRANCH_8:
				imm = (nibs[2] << 4) | (nibs[3]);
				if (imm & 0x80)
					imm |= ~0xff;
				imm = ((char)imm) * 2 + 4 ;
				goto ok;
			case BRANCH_12:
				imm = ((nibs[1]) << 8) | (nibs[2] << 4) | (nibs[3]);
				if (imm & 0x800)
					imm |= ~0xfff;
				imm = imm * 2 + 4;
				goto ok;
			case IMM_4:
				imm = nibs[3];
				goto ok;
			case IMM_4BY2:
				imm = nibs[3] <<1;
				goto ok;
			case IMM_4BY4:
				imm = nibs[3] <<2;
				goto ok;
			case IMM_8:
				imm = (nibs[2] << 4) | nibs[3];
				goto ok;
			case PCRELIMM_8BY2:
				imm = ((nibs[2] << 4) | nibs[3]) <<1;
				relmask = ~1;
				goto ok;
			case PCRELIMM_8BY4:
				imm = ((nibs[2] << 4) | nibs[3]) <<2;
				relmask = ~3;
				goto ok;
			case IMM_8BY2:
				imm = ((nibs[2] << 4) | nibs[3]) <<1;
				goto ok;
			case IMM_8BY4:
				imm = ((nibs[2] << 4) | nibs[3]) <<2;
				goto ok;
			case DISP_8:
				imm = (nibs[2] << 4) | (nibs[3]);
				goto ok;
			case DISP_4:
				imm = nibs[3];
				goto ok;
			case REG_N:
				rn = nibs[n];
				break;
			case REG_M:
				rm = nibs[n];
				break;
			case REG_NM:
				rn = (nibs[n] & 0xc) >> 2;
				rm = (nibs[n] & 0x3);
				break;
			case REG_B:
				rb = nibs[n] & 0x07;
				break;
			default:
				return;
			}
		}

	ok:
		printk("%-8s  ", op->name);
		lastsp = (op->arg[0] == A_END);
		disp_pc = 0;
		for (n = 0; n < 6 && op->arg[n] != A_END; n++) {
			if (n && op->arg[1] != A_END)
				printk(", ");
			switch (op->arg[n]) {
			case A_IMM:
				printk("#%d", (char)(imm));
				break;
			case A_R0:
				printk("r0");
				break;
			case A_REG_N:
				printk("r%d", rn);
				break;
			case A_INC_N:
				printk("@r%d+", rn);
				break;
			case A_DEC_N:
				printk("@-r%d", rn);
				break;
			case A_IND_N:
				printk("@r%d", rn);
				break;
			case A_DISP_REG_N:
				printk("@(%d,r%d)", imm, rn);
				break;
			case A_REG_M:
				printk("r%d", rm);
				break;
			case A_INC_M:
				printk("@r%d+", rm);
				break;
			case A_DEC_M:
				printk("@-r%d", rm);
				break;
			case A_IND_M:
				printk("@r%d", rm);
				break;
			case A_DISP_REG_M:
				printk("@(%d,r%d)", imm, rm);
				break;
			case A_REG_B:
				printk("r%d_bank", rb);
				break;
			case A_DISP_PC:
				disp_pc = 1;
				disp_pc_addr = imm + 4 + (memaddr & relmask);
				printk("%08x <%pS>", disp_pc_addr,
				       (void *)disp_pc_addr);
				break;
			case A_IND_R0_REG_N:
				printk("@(r0,r%d)", rn);
				break;
			case A_IND_R0_REG_M:
				printk("@(r0,r%d)", rm);
				break;
			case A_DISP_GBR:
				printk("@(%d,gbr)",imm);
				break;
			case A_R0_GBR:
				printk("@(r0,gbr)");
				break;
			case A_BDISP12:
			case A_BDISP8:
				printk("%08x", imm + memaddr);
				break;
			case A_SR:
				printk("sr");
				break;
			case A_GBR:
				printk("gbr");
				break;
			case A_VBR:
				printk("vbr");
				break;
			case A_SSR:
				printk("ssr");
				break;
			case A_SPC:
				printk("spc");
				break;
			case A_MACH:
				printk("mach");
				break;
			case A_MACL:
				printk("macl");
				break;
			case A_PR:
				printk("pr");
				break;
			case A_SGR:
				printk("sgr");
				break;
			case A_DBR:
				printk("dbr");
				break;
			case FD_REG_N:
			case F_REG_N:
				printk("fr%d", rn);
				break;
			case F_REG_M:
				printk("fr%d", rm);
				break;
			case DX_REG_N:
				if (rn & 1) {
					printk("xd%d", rn & ~1);
					break;
				}
				/* else, fall through */
			case D_REG_N:
				printk("dr%d", rn);
				break;
			case DX_REG_M:
				if (rm & 1) {
					printk("xd%d", rm & ~1);
					break;
				}
				/* else, fall through */
			case D_REG_M:
				printk("dr%d", rm);
				break;
			case FPSCR_M:
			case FPSCR_N:
				printk("fpscr");
				break;
			case FPUL_M:
			case FPUL_N:
				printk("fpul");
				break;
			case F_FR0:
				printk("fr0");
				break;
			case V_REG_N:
				printk("fv%d", rn*4);
				break;
			case V_REG_M:
				printk("fv%d", rm*4);
				break;
			case XMTRX_M4:
				printk("xmtrx");
				break;
			default:
				return;
			}
		}

		if (disp_pc && strcmp(op->name, "mova") != 0) {
			u32 val;

			if (relmask == ~1)
				__get_user(val, (u16 *)disp_pc_addr);
			else
				__get_user(val, (u32 *)disp_pc_addr);

			printk("  ! %08x <%pS>", val, (void *)val);
		}

		return;
	fail:
		;

	}

	printk(".word 0x%x%x%x%x", nibs[0], nibs[1], nibs[2], nibs[3]);
}