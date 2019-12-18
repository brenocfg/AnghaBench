#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_2__ {int csum_flags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int CSUM_DELAY_DATA ; 
 int CSUM_DELAY_DATA_IPV6 ; 
 int /*<<< orphan*/  pf_cksum_fixup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int16_t
pf_proto_cksum_fixup(struct mbuf *m, u_int16_t cksum, u_int16_t old,
        u_int16_t new, u_int8_t udp)
{
	if (m->m_pkthdr.csum_flags & (CSUM_DELAY_DATA | CSUM_DELAY_DATA_IPV6))
		return (cksum);

	return (pf_cksum_fixup(cksum, old, new, udp));
}