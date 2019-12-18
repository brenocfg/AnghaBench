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
typedef  int uint8_t ;
struct TYPE_5__ {int intx; int abrt; } ;
struct TYPE_6__ {TYPE_1__ tsx; } ;
struct TYPE_7__ {TYPE_2__ bits; int /*<<< orphan*/  leaf; } ;
struct TYPE_8__ {TYPE_3__ mode; } ;
struct pt_packet {TYPE_4__ payload; int /*<<< orphan*/  type; } ;
struct pt_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppt_mode ; 
 int pt_enc_next (struct pt_encoder*,struct pt_packet*) ; 
 int pt_mob_tsx_abrt ; 
 int pt_mob_tsx_intx ; 
 int /*<<< orphan*/  pt_mol_tsx ; 

int pt_encode_mode_tsx(struct pt_encoder *encoder, uint8_t bits)
{
	struct pt_packet packet;

	packet.type = ppt_mode;
	packet.payload.mode.leaf = pt_mol_tsx;

	if (bits & pt_mob_tsx_intx)
		packet.payload.mode.bits.tsx.intx = 1;
	else
		packet.payload.mode.bits.tsx.intx = 0;

	if (bits & pt_mob_tsx_abrt)
		packet.payload.mode.bits.tsx.abrt = 1;
	else
		packet.payload.mode.bits.tsx.abrt = 0;

	return pt_enc_next(encoder, &packet);
}