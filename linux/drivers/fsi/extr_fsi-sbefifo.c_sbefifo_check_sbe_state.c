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
typedef  int u32 ;
struct sbefifo {int async_ffdc; TYPE_1__* fsi_dev; } ;
typedef  int /*<<< orphan*/  raw_word ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFAM_GP_MBOX_SBM_ADDR ; 
 int CFAM_SBM_SBE_ASYNC_FFDC ; 
 int CFAM_SBM_SBE_BOOTED ; 
 int CFAM_SBM_SBE_STATE_MASK ; 
 int CFAM_SBM_SBE_STATE_SHIFT ; 
 int EBUSY ; 
 int ESHUTDOWN ; 
#define  SBE_STATE_DMT 136 
#define  SBE_STATE_DUMP 135 
#define  SBE_STATE_FAILURE 134 
#define  SBE_STATE_IPLING 133 
#define  SBE_STATE_ISTEP 132 
#define  SBE_STATE_MPIPL 131 
#define  SBE_STATE_QUIESCE 130 
#define  SBE_STATE_RUNTIME 129 
#define  SBE_STATE_UNKNOWN 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int fsi_slave_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sbefifo_check_sbe_state(struct sbefifo *sbefifo)
{
	__be32 raw_word;
	u32 sbm;
	int rc;

	rc = fsi_slave_read(sbefifo->fsi_dev->slave, CFAM_GP_MBOX_SBM_ADDR,
			    &raw_word, sizeof(raw_word));
	if (rc)
		return rc;
	sbm = be32_to_cpu(raw_word);

	/* SBE booted at all ? */
	if (!(sbm & CFAM_SBM_SBE_BOOTED))
		return -ESHUTDOWN;

	/* Check its state */
	switch ((sbm & CFAM_SBM_SBE_STATE_MASK) >> CFAM_SBM_SBE_STATE_SHIFT) {
	case SBE_STATE_UNKNOWN:
		return -ESHUTDOWN;
	case SBE_STATE_DMT:
		return -EBUSY;
	case SBE_STATE_IPLING:
	case SBE_STATE_ISTEP:
	case SBE_STATE_MPIPL:
	case SBE_STATE_RUNTIME:
	case SBE_STATE_DUMP: /* Not sure about that one */
		break;
	case SBE_STATE_FAILURE:
	case SBE_STATE_QUIESCE:
		return -ESHUTDOWN;
	}

	/* Is there async FFDC available ? Remember it */
	if (sbm & CFAM_SBM_SBE_ASYNC_FFDC)
		sbefifo->async_ffdc = true;

	return 0;
}