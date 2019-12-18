#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_6__ {int sccrx_empty; int scctx_empty; int e1_first_int; scalar_t__ scctx_e; scalar_t__ scctx_b; scalar_t__ sccrx_e; scalar_t__ sccrx_b; scalar_t__ call_on_err; scalar_t__ call_on_scc; scalar_t__ call_on_msig; scalar_t__ call_on_rx; scalar_t__ call_on_tx; } ;
typedef  TYPE_1__ ct_chan_t ;
struct TYPE_7__ {int type; TYPE_1__* chan; } ;
typedef  TYPE_2__ ct_board_t ;
typedef  int /*<<< orphan*/  cr_dat_tst_t ;

/* Variables and functions */
#define  B_TAU2 133 
#define  B_TAU2_E1 132 
#define  B_TAU2_E1D 131 
#define  B_TAU2_G703 130 
#define  B_TAU_E1 129 
#define  B_TAU_G703 128 
 int NBRD ; 
 int NCHAN ; 
 int /*<<< orphan*/  ct_init (TYPE_2__*,int,int /*<<< orphan*/ ,int,int,unsigned char*,long,int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  ct_probe_board (int /*<<< orphan*/ ,int,int) ; 
 int ct_setup_board (TYPE_2__*,unsigned char const*,long,int /*<<< orphan*/  const*) ; 
 unsigned char* ctau2_fw_data ; 
 unsigned char* ctau_fw_data ; 
 long ctau_fw_len ; 
 int /*<<< orphan*/ * ctau_fw_tvec ; 
 unsigned char* ctaue1_fw_data ; 
 long ctaue1_fw_len ; 
 int /*<<< orphan*/ * ctaue1_fw_tvec ; 
 unsigned char* ctaug703_fw_data ; 
 long ctaug703_fw_len ; 
 int /*<<< orphan*/ * ctaug703_fw_tvec ; 

int ct_open_board (ct_board_t *b, int num, port_t port, int irq, int dma)
{
	ct_chan_t *c;
	const unsigned char *fw;
	const cr_dat_tst_t *ft;
	long flen;

	if (num >= NBRD || ! ct_probe_board (port, irq, dma))
		return 0;

	/* init callback pointers */
	for (c=b->chan; c<b->chan+NCHAN; ++c) {
		c->call_on_tx = 0;
		c->call_on_rx = 0;
		c->call_on_msig = 0;
		c->call_on_scc = 0;
		c->call_on_err = 0;
	}

	/* init DDK channel variables */
	for (c=b->chan; c<b->chan+NCHAN; ++c) {
		c->sccrx_empty = c->scctx_empty = 1;
		c->sccrx_b = c->sccrx_e = 0;
		c->scctx_b = c->scctx_e = 0;
		c->e1_first_int = 1;
	}

	/* init board structure */
	ct_init (b, num, port, irq, dma, ctau_fw_data, 
		ctau_fw_len, ctau_fw_tvec, ctau2_fw_data);

	/* determine which firmware should be loaded */
	fw = ctau_fw_data;
	flen = ctau_fw_len;
	ft = ctau_fw_tvec;
	switch (b->type) {
	case B_TAU2:
	case B_TAU2_G703:
	case B_TAU2_E1:
	case B_TAU2_E1D:
		fw = ctau2_fw_data;
		flen = 0;
		ft = NULL;
		break;
#ifndef CT_DDK_NO_G703
	case B_TAU_G703:
		fw = ctaug703_fw_data;
		flen = ctaug703_fw_len;
		ft = ctaug703_fw_tvec;
		break;
#endif
#ifndef CT_DDK_NO_E1
	case B_TAU_E1:
		fw = ctaue1_fw_data;
		flen = ctaue1_fw_len;
		ft = ctaue1_fw_tvec;
		break;
#endif
	}
	/* Load firmware and set up board */
	return ct_setup_board (b, fw, flen, ft);
}