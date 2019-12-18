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
struct ptunit_result {int dummy; } ;
struct pt_packet_decoder {int dummy; } ;
struct pt_packet {int dummy; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int pt_pkt_next (struct pt_packet_decoder*,struct pt_packet*,int) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result next_null(void)
{
	struct pt_packet_decoder decoder;
	struct pt_packet packet;
	int errcode;

	errcode = pt_pkt_next(NULL, &packet, sizeof(packet));
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_pkt_next(&decoder, NULL, sizeof(packet));
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}