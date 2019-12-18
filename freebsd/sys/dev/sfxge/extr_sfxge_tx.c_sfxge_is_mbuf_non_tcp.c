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
struct TYPE_2__ {int csum_flags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int CSUM_IP6_TCP ; 
 int CSUM_IP_TCP ; 

__attribute__((used)) static unsigned int
sfxge_is_mbuf_non_tcp(struct mbuf *mbuf)
{
	/* Absence of TCP checksum flags does not mean that it is non-TCP
	 * but it should be true if user wants to achieve high throughput.
	 */
	return (!(mbuf->m_pkthdr.csum_flags & (CSUM_IP_TCP | CSUM_IP6_TCP)));
}