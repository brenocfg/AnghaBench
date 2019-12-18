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
struct r92c_tx_desc {int /*<<< orphan*/  txdseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  R88E_TXDSEQ_HWSEQ_EN ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 

void
r88e_tx_setup_hwseq(void *buf)
{
	struct r92c_tx_desc *txd = (struct r92c_tx_desc *)buf;

	txd->txdseq |= htole16(R88E_TXDSEQ_HWSEQ_EN);
}