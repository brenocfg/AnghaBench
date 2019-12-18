#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eeh_pe {int config_addr; int addr; TYPE_1__* phb; } ;
struct TYPE_2__ {int /*<<< orphan*/  buid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUID_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUID_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_TYPE_RTAS_LOG ; 
 int /*<<< orphan*/  eeh_error_buf_size ; 
 int /*<<< orphan*/  ibm_slot_error_detail ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* slot_errbuf ; 
 int /*<<< orphan*/  slot_errbuf_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_to_phys (char*) ; 

__attribute__((used)) static int pseries_eeh_get_log(struct eeh_pe *pe, int severity, char *drv_log, unsigned long len)
{
	int config_addr;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&slot_errbuf_lock, flags);
	memset(slot_errbuf, 0, eeh_error_buf_size);

	/* Figure out the PE address */
	config_addr = pe->config_addr;
	if (pe->addr)
		config_addr = pe->addr;

	ret = rtas_call(ibm_slot_error_detail, 8, 1, NULL, config_addr,
			BUID_HI(pe->phb->buid), BUID_LO(pe->phb->buid),
			virt_to_phys(drv_log), len,
			virt_to_phys(slot_errbuf), eeh_error_buf_size,
			severity);
	if (!ret)
		log_error(slot_errbuf, ERR_TYPE_RTAS_LOG, 0);
	spin_unlock_irqrestore(&slot_errbuf_lock, flags);

	return ret;
}