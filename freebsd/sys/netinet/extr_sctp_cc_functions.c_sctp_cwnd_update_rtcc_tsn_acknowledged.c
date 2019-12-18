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
struct sctp_tmit_chunk {scalar_t__ send_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  bw_bytes; } ;
struct TYPE_4__ {TYPE_1__ rtcc; } ;
struct sctp_nets {TYPE_2__ cc_mod; } ;

/* Variables and functions */

__attribute__((used)) static
void
sctp_cwnd_update_rtcc_tsn_acknowledged(struct sctp_nets *net,
    struct sctp_tmit_chunk *tp1)
{
	net->cc_mod.rtcc.bw_bytes += tp1->send_size;
}