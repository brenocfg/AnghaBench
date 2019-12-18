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
struct al_udma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_UDMA_PRINT_REG (struct al_udma*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_dbg (char*) ; 
 int /*<<< orphan*/  axi_data_fifo_status ; 
 int /*<<< orphan*/  check_en ; 
 int /*<<< orphan*/  err_log_mask ; 
 int /*<<< orphan*/  fifo_en ; 
 int /*<<< orphan*/  log_0 ; 
 int /*<<< orphan*/  log_1 ; 
 int /*<<< orphan*/  log_2 ; 
 int /*<<< orphan*/  log_3 ; 
 int /*<<< orphan*/  s2m ; 
 int /*<<< orphan*/  s_data_fifo_status ; 
 int /*<<< orphan*/  s_header_fifo_status ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  stream_cfg ; 
 int /*<<< orphan*/  unack_fifo_status ; 

__attribute__((used)) static void al_udma_regs_s2m_general_print(struct al_udma *udma)
{
	al_dbg("S2M general regs:\n");
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, state);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, err_log_mask);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, log_0);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, log_1);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, log_2);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, log_3);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, s_data_fifo_status);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, s_header_fifo_status);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, axi_data_fifo_status);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, unack_fifo_status);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, check_en);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, fifo_en);
	AL_UDMA_PRINT_REG(udma, " ", "\n", s2m, s2m, stream_cfg);
}