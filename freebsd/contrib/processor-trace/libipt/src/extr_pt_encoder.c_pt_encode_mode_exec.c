#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  exec; } ;
struct TYPE_5__ {TYPE_1__ bits; int /*<<< orphan*/  leaf; } ;
struct TYPE_6__ {TYPE_2__ mode; } ;
struct pt_packet {TYPE_3__ payload; int /*<<< orphan*/  type; } ;
struct pt_encoder {int dummy; } ;
typedef  enum pt_exec_mode { ____Placeholder_pt_exec_mode } pt_exec_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ppt_mode ; 
 int pt_enc_next (struct pt_encoder*,struct pt_packet*) ; 
 int /*<<< orphan*/  pt_mol_exec ; 
 int /*<<< orphan*/  pt_set_exec_mode (int) ; 

int pt_encode_mode_exec(struct pt_encoder *encoder, enum pt_exec_mode mode)
{
	struct pt_packet packet;

	packet.type = ppt_mode;
	packet.payload.mode.leaf = pt_mol_exec;
	packet.payload.mode.bits.exec = pt_set_exec_mode(mode);

	return pt_enc_next(encoder, &packet);
}