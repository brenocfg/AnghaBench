#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int dmaaddr; } ;
struct TYPE_7__ {TYPE_4__ buf; TYPE_2__* atmvcc; } ;
struct lanai_vcc {TYPE_3__ rx; } ;
typedef  int dma_addr_t ;
struct TYPE_5__ {scalar_t__ aal; } ;
struct TYPE_6__ {TYPE_1__ qos; } ;

/* Variables and functions */
 scalar_t__ ATM_AAL5 ; 
 int /*<<< orphan*/  RMMODE_PRESERVE ; 
 int /*<<< orphan*/  RMMODE_TRASH ; 
 int RXADDR1_OAM_PRESERVE ; 
 int RXADDR1_SET_MODE (int /*<<< orphan*/ ) ; 
 int RXADDR1_SET_RMMODE (int /*<<< orphan*/ ) ; 
 int RXADDR1_SET_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXMODE_AAL0 ; 
 int /*<<< orphan*/  RXMODE_AAL5 ; 
 int /*<<< orphan*/  cardvcc_write (struct lanai_vcc const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lanai_buf_size_cardorder (TYPE_4__*) ; 
 int /*<<< orphan*/  vcc_rxaddr1 ; 
 int /*<<< orphan*/  vcc_rxaddr2 ; 
 int /*<<< orphan*/  vcc_rxbufstart ; 
 int /*<<< orphan*/  vcc_rxcrc1 ; 
 int /*<<< orphan*/  vcc_rxcrc2 ; 
 int /*<<< orphan*/  vcc_rxreadptr ; 
 int /*<<< orphan*/  vcc_rxwriteptr ; 

__attribute__((used)) static void host_vcc_start_rx(const struct lanai_vcc *lvcc)
{
	u32 addr1;
	if (lvcc->rx.atmvcc->qos.aal == ATM_AAL5) {
		dma_addr_t dmaaddr = lvcc->rx.buf.dmaaddr;
		cardvcc_write(lvcc, 0xFFFF, vcc_rxcrc1);
		cardvcc_write(lvcc, 0xFFFF, vcc_rxcrc2);
		cardvcc_write(lvcc, 0, vcc_rxwriteptr);
		cardvcc_write(lvcc, 0, vcc_rxbufstart);
		cardvcc_write(lvcc, 0, vcc_rxreadptr);
		cardvcc_write(lvcc, (dmaaddr >> 16) & 0xFFFF, vcc_rxaddr2);
		addr1 = ((dmaaddr >> 8) & 0xFF) |
		    RXADDR1_SET_SIZE(lanai_buf_size_cardorder(&lvcc->rx.buf))|
		    RXADDR1_SET_RMMODE(RMMODE_TRASH) |	/* ??? */
		 /* RXADDR1_OAM_PRESERVE |	--- no OAM support yet */
		    RXADDR1_SET_MODE(RXMODE_AAL5);
	} else
		addr1 = RXADDR1_SET_RMMODE(RMMODE_PRESERVE) | /* ??? */
		    RXADDR1_OAM_PRESERVE |		      /* ??? */
		    RXADDR1_SET_MODE(RXMODE_AAL0);
	/* This one must be last! */
	cardvcc_write(lvcc, addr1, vcc_rxaddr1);
}