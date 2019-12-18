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
typedef  int uint32_t ;
struct ptunit_result {int dummy; } ;
struct pt_packet_ip {int ipc; unsigned long long ip; } ;
struct pt_last_ip {int ip; int have_ip; int suppressed; } ;
typedef  enum pt_ip_compression { ____Placeholder_pt_ip_compression } pt_ip_compression ;

/* Variables and functions */
 int pt_last_ip_update_ip (struct pt_last_ip*,struct pt_packet_ip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_bad_packet ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int,int) ; 

__attribute__((used)) static struct ptunit_result update_ip_bad_packet(uint32_t have_ip)
{
	struct pt_last_ip last_ip;
	struct pt_packet_ip packet;
	int errcode;

	last_ip.ip = 0x7fffffffffffffffull;
	last_ip.have_ip = have_ip;
	last_ip.suppressed = 0;

	packet.ipc = (enum pt_ip_compression) 0xff;
	packet.ip = 0ull;

	errcode = pt_last_ip_update_ip(&last_ip, &packet, NULL);
	ptu_int_eq(errcode, -pte_bad_packet);
	ptu_uint_eq(last_ip.ip, 0x7fffffffffffffffull);
	ptu_uint_eq(last_ip.have_ip, have_ip);
	ptu_uint_eq(last_ip.suppressed, 0);

	return ptu_passed();
}