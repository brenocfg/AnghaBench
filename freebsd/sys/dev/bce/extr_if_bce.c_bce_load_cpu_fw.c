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
typedef  scalar_t__ u32 ;
struct fw_info {int text_len; int data_len; int sbss_len; int bss_len; int rodata_len; int /*<<< orphan*/  start_addr; int /*<<< orphan*/ * rodata; scalar_t__ rodata_addr; int /*<<< orphan*/ * bss; scalar_t__ bss_addr; int /*<<< orphan*/ * sbss; scalar_t__ sbss_addr; int /*<<< orphan*/ * data; scalar_t__ data_addr; int /*<<< orphan*/ * text; scalar_t__ text_addr; } ;
struct cpu_reg {scalar_t__ pc; scalar_t__ inst; scalar_t__ mips_view_base; scalar_t__ spad_base; } ;
struct bce_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR_IND (struct bce_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_halt_cpu (struct bce_softc*,struct cpu_reg*) ; 

__attribute__((used)) static void
bce_load_cpu_fw(struct bce_softc *sc, struct cpu_reg *cpu_reg,
	struct fw_info *fw)
{
	u32 offset;

	DBENTER(BCE_VERBOSE_RESET);

    bce_halt_cpu(sc, cpu_reg);

	/* Load the Text area. */
	offset = cpu_reg->spad_base + (fw->text_addr - cpu_reg->mips_view_base);
	if (fw->text) {
		int j;

		for (j = 0; j < (fw->text_len / 4); j++, offset += 4) {
			REG_WR_IND(sc, offset, fw->text[j]);
	        }
	}

	/* Load the Data area. */
	offset = cpu_reg->spad_base + (fw->data_addr - cpu_reg->mips_view_base);
	if (fw->data) {
		int j;

		for (j = 0; j < (fw->data_len / 4); j++, offset += 4) {
			REG_WR_IND(sc, offset, fw->data[j]);
		}
	}

	/* Load the SBSS area. */
	offset = cpu_reg->spad_base + (fw->sbss_addr - cpu_reg->mips_view_base);
	if (fw->sbss) {
		int j;

		for (j = 0; j < (fw->sbss_len / 4); j++, offset += 4) {
			REG_WR_IND(sc, offset, fw->sbss[j]);
		}
	}

	/* Load the BSS area. */
	offset = cpu_reg->spad_base + (fw->bss_addr - cpu_reg->mips_view_base);
	if (fw->bss) {
		int j;

		for (j = 0; j < (fw->bss_len/4); j++, offset += 4) {
			REG_WR_IND(sc, offset, fw->bss[j]);
		}
	}

	/* Load the Read-Only area. */
	offset = cpu_reg->spad_base +
		(fw->rodata_addr - cpu_reg->mips_view_base);
	if (fw->rodata) {
		int j;

		for (j = 0; j < (fw->rodata_len / 4); j++, offset += 4) {
			REG_WR_IND(sc, offset, fw->rodata[j]);
		}
	}

	/* Clear the pre-fetch instruction and set the FW start address. */
	REG_WR_IND(sc, cpu_reg->inst, 0);
	REG_WR_IND(sc, cpu_reg->pc, fw->start_addr);

	DBEXIT(BCE_VERBOSE_RESET);
}