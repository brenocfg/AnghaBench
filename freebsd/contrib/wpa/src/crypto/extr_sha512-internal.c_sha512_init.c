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
struct sha512_state {void** state; scalar_t__ length; scalar_t__ curlen; } ;

/* Variables and functions */
 void* CONST64 (int) ; 

void sha512_init(struct sha512_state *md)
{
	md->curlen = 0;
	md->length = 0;
	md->state[0] = CONST64(0x6a09e667f3bcc908);
	md->state[1] = CONST64(0xbb67ae8584caa73b);
	md->state[2] = CONST64(0x3c6ef372fe94f82b);
	md->state[3] = CONST64(0xa54ff53a5f1d36f1);
	md->state[4] = CONST64(0x510e527fade682d1);
	md->state[5] = CONST64(0x9b05688c2b3e6c1f);
	md->state[6] = CONST64(0x1f83d9abfb41bd6b);
	md->state[7] = CONST64(0x5be0cd19137e2179);
}