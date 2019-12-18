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
typedef  int u_int ;
struct fw_eth_tx_pkt_wr {int dummy; } ;
struct cpl_tx_pkt_core {int dummy; } ;

/* Variables and functions */
 int EQ_ESIZE ; 

__attribute__((used)) static inline u_int
imm_payload(u_int ndesc)
{
	u_int n;

	n = ndesc * EQ_ESIZE - sizeof(struct fw_eth_tx_pkt_wr) -
	    sizeof(struct cpl_tx_pkt_core);

	return (n);
}