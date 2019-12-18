#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pnp_set_config_arg {int csn; int ldn; } ;
struct isa_config {int ic_nmem; int ic_nport; int ic_nirq; int ic_ndrq; scalar_t__* ic_irqmask; scalar_t__* ic_drqmask; TYPE_2__* ic_port; TYPE_1__* ic_mem; } ;
struct TYPE_4__ {scalar_t__ ir_size; int ir_start; } ;
struct TYPE_3__ {scalar_t__ ir_size; int ir_start; } ;

/* Variables and functions */
 int ISA_PNP_NDRQ ; 
 int ISA_PNP_NIRQ ; 
 int ISA_PNP_NMEM ; 
 int ISA_PNP_NPORT ; 
 int /*<<< orphan*/  PNP_ACTIVATE ; 
 int /*<<< orphan*/  PNP_CONFIG_CONTROL ; 
 int PNP_CONFIG_CONTROL_WAIT_FOR_KEY ; 
 int /*<<< orphan*/  PNP_DMA_CHANNEL (int) ; 
 int /*<<< orphan*/  PNP_IO_BASE_HIGH (int) ; 
 int /*<<< orphan*/  PNP_IO_BASE_LOW (int) ; 
 int /*<<< orphan*/  PNP_IRQ_LEVEL (int) ; 
 int /*<<< orphan*/  PNP_IRQ_TYPE (int) ; 
 int /*<<< orphan*/  PNP_MEM_BASE_HIGH (int) ; 
 int /*<<< orphan*/  PNP_MEM_BASE_LOW (int) ; 
 int /*<<< orphan*/  PNP_MEM_RANGE_HIGH (int) ; 
 int /*<<< orphan*/  PNP_MEM_RANGE_LOW (int) ; 
 int /*<<< orphan*/  PNP_SET_LDN ; 
 int /*<<< orphan*/  PNP_WAKE ; 
 int ffs (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pnp_send_initiation_key () ; 
 int /*<<< orphan*/  pnp_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void
pnp_set_config(void *arg, struct isa_config *config, int enable)
{
	int csn = ((struct pnp_set_config_arg *) arg)->csn;
	int ldn = ((struct pnp_set_config_arg *) arg)->ldn;
	int i;

	/*
	 * First put all cards into Sleep state with the initiation
	 * key, then put our card into Config state.
	 */
	pnp_send_initiation_key();
	pnp_write(PNP_WAKE, csn);

	/*
	 * Select our logical device so that we can program it.
	 */
	pnp_write(PNP_SET_LDN, ldn);

	/*
	 * Constrain the number of resources we will try to program
	 */
	if (config->ic_nmem > ISA_PNP_NMEM) {
		printf("too many ISA memory ranges (%d > %d)\n",
		    config->ic_nmem, ISA_PNP_NMEM);
		config->ic_nmem = ISA_PNP_NMEM;
	}
	if (config->ic_nport > ISA_PNP_NPORT) {
		printf("too many ISA I/O ranges (%d > %d)\n", config->ic_nport,
		    ISA_PNP_NPORT);
		config->ic_nport = ISA_PNP_NPORT;
	}
	if (config->ic_nirq > ISA_PNP_NIRQ) {
		printf("too many ISA IRQs (%d > %d)\n", config->ic_nirq,
		    ISA_PNP_NIRQ);
		config->ic_nirq = ISA_PNP_NIRQ;
	}
	if (config->ic_ndrq > ISA_PNP_NDRQ) {
		printf("too many ISA DRQs (%d > %d)\n", config->ic_ndrq,
		    ISA_PNP_NDRQ);
		config->ic_ndrq = ISA_PNP_NDRQ;
	}

	/*
	 * Now program the resources.
	 */
	for (i = 0; i < config->ic_nmem; i++) {
		uint32_t start;
		uint32_t size;

		/* XXX: should handle memory control register, 32 bit memory */
		if (config->ic_mem[i].ir_size == 0) {
			pnp_write(PNP_MEM_BASE_HIGH(i), 0);
			pnp_write(PNP_MEM_BASE_LOW(i), 0);
			pnp_write(PNP_MEM_RANGE_HIGH(i), 0);
			pnp_write(PNP_MEM_RANGE_LOW(i), 0);
		} else {
			start = config->ic_mem[i].ir_start;
			size =  config->ic_mem[i].ir_size;
			if (start & 0xff)
				panic("pnp_set_config: bogus memory assignment");
			pnp_write(PNP_MEM_BASE_HIGH(i), (start >> 16) & 0xff);
			pnp_write(PNP_MEM_BASE_LOW(i), (start >> 8) & 0xff);
			pnp_write(PNP_MEM_RANGE_HIGH(i), (size >> 16) & 0xff);
			pnp_write(PNP_MEM_RANGE_LOW(i), (size >> 8) & 0xff);
		}
	}
	for (; i < ISA_PNP_NMEM; i++) {
		pnp_write(PNP_MEM_BASE_HIGH(i), 0);
		pnp_write(PNP_MEM_BASE_LOW(i), 0);
		pnp_write(PNP_MEM_RANGE_HIGH(i), 0);
		pnp_write(PNP_MEM_RANGE_LOW(i), 0);
	}

	for (i = 0; i < config->ic_nport; i++) {
		uint32_t start;

		if (config->ic_port[i].ir_size == 0) {
			pnp_write(PNP_IO_BASE_HIGH(i), 0);
			pnp_write(PNP_IO_BASE_LOW(i), 0);
		} else {
			start = config->ic_port[i].ir_start;
			pnp_write(PNP_IO_BASE_HIGH(i), (start >> 8) & 0xff);
			pnp_write(PNP_IO_BASE_LOW(i), (start >> 0) & 0xff);
		}
	}
	for (; i < ISA_PNP_NPORT; i++) {
		pnp_write(PNP_IO_BASE_HIGH(i), 0);
		pnp_write(PNP_IO_BASE_LOW(i), 0);
	}

	for (i = 0; i < config->ic_nirq; i++) {
		int irq;

		/* XXX: interrupt type */
		if (config->ic_irqmask[i] == 0) {
			pnp_write(PNP_IRQ_LEVEL(i), 0);
			pnp_write(PNP_IRQ_TYPE(i), 2);
		} else {
			irq = ffs(config->ic_irqmask[i]) - 1;
			pnp_write(PNP_IRQ_LEVEL(i), irq);
			pnp_write(PNP_IRQ_TYPE(i), 2); /* XXX */
		}
	}
	for (; i < ISA_PNP_NIRQ; i++) {
		/*
		 * IRQ 0 is not a valid interrupt selection and
		 * represents no interrupt selection.
		 */
		pnp_write(PNP_IRQ_LEVEL(i), 0);
		pnp_write(PNP_IRQ_TYPE(i), 2);
	}		

	for (i = 0; i < config->ic_ndrq; i++) {
		int drq;

		if (config->ic_drqmask[i] == 0) {
			pnp_write(PNP_DMA_CHANNEL(i), 4);
		} else {
			drq = ffs(config->ic_drqmask[i]) - 1;
			pnp_write(PNP_DMA_CHANNEL(i), drq);
		}
	}
	for (; i < ISA_PNP_NDRQ; i++) {
		/*
		 * DMA channel 4, the cascade channel is used to
		 * indicate no DMA channel is active.
		 */
		pnp_write(PNP_DMA_CHANNEL(i), 4);
	}		

	pnp_write(PNP_ACTIVATE, enable ? 1 : 0);

	/*
	 * Wake everyone up again, we are finished.
	 */
	pnp_write(PNP_CONFIG_CONTROL, PNP_CONFIG_CONTROL_WAIT_FOR_KEY);
}