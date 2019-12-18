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
typedef  scalar_t__ uint16_t ;
struct tcphdr {int th_sum; scalar_t__ th_off; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t
tcp_lro_csum_th(struct tcphdr *th)
{
	uint32_t ch;
	uint16_t *p, l;

	ch = th->th_sum = 0x0000;
	l = th->th_off;
	p = (uint16_t *)th;
	while (l > 0) {
		ch += *p;
		p++;
		ch += *p;
		p++;
		l--;
	}
	while (ch > 0xffff)
		ch = (ch >> 16) + (ch & 0xffff);

	return (ch & 0xffff);
}