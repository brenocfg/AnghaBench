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
typedef  int /*<<< orphan*/  u64 ;
struct ulp_txpkt {void* len; void* cmd_dest; } ;
struct cpl_set_tcb_field {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULP_TXPKT ; 
 int /*<<< orphan*/  V_ULPTX_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ULPTX_NFLITS (int) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_set_tcb_field (struct cpl_set_tcb_field*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_tcb_field_ulp(struct cpl_set_tcb_field *req, unsigned int tid,
    unsigned int word, u64 mask, u64 val)
{
	struct ulp_txpkt *txpkt = (struct ulp_txpkt *)req;

	txpkt->cmd_dest = htonl(V_ULPTX_CMD(ULP_TXPKT));
	txpkt->len = htonl(V_ULPTX_NFLITS(sizeof(*req) / 8));
	mk_set_tcb_field(req, tid, word, mask, val);
}