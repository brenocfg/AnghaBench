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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {TYPE_1__ cyc; } ;
struct pt_packet {TYPE_2__ payload; int /*<<< orphan*/  type; } ;
struct pt_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppt_cyc ; 
 int pt_enc_next (struct pt_encoder*,struct pt_packet*) ; 

int pt_encode_cyc(struct pt_encoder *encoder, uint32_t ctc)
{
	struct pt_packet packet;

	packet.type = ppt_cyc;
	packet.payload.cyc.value = ctc;

	return pt_enc_next(encoder, &packet);
}