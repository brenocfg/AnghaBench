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
struct csum_state {int val; } ;

/* Variables and functions */

void
csum32_update(uint8_t *p, uint32_t len, struct csum_state *css)
{
	uint32_t t;

	for ( ; len > 3; len -= 4, p += 4 ) {
		t = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
		css->val ^= t;
	}
}