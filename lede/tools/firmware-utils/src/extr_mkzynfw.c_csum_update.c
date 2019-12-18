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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct csum_state {int odd; int sum; int tmp; } ;

/* Variables and functions */

void
csum_update(uint8_t *p, uint32_t len, struct csum_state *css)
{
	if (len == 0)
		return;

	if (css->odd) {
		css->sum += (css->tmp << 8) + p[0];
		if (css->sum > 0xFFFF) {
			css->sum += 1;
			css->sum &= 0xFFFF;
		}
		css->odd = 0;
		len--;
		p++;
	}

	for ( ; len > 1; len -= 2, p +=2 ) {
		css->sum  += (p[0] << 8) + p[1];
		if (css->sum > 0xFFFF) {
			css->sum += 1;
			css->sum &= 0xFFFF;
		}
	}

	if (len == 1){
		css->tmp = p[0];
		css->odd = 1;
	}
}