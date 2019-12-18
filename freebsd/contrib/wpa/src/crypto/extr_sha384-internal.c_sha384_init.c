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
struct sha384_state {void** state; scalar_t__ length; scalar_t__ curlen; } ;

/* Variables and functions */
 void* CONST64 (int) ; 

void sha384_init(struct sha384_state *md)
{
	md->curlen = 0;
	md->length = 0;
	md->state[0] = CONST64(0xcbbb9d5dc1059ed8);
	md->state[1] = CONST64(0x629a292a367cd507);
	md->state[2] = CONST64(0x9159015a3070dd17);
	md->state[3] = CONST64(0x152fecd8f70e5939);
	md->state[4] = CONST64(0x67332667ffc00b31);
	md->state[5] = CONST64(0x8eb44a8768581511);
	md->state[6] = CONST64(0xdb0c2e0d64f98fa7);
	md->state[7] = CONST64(0x47b5481dbefa4fa4);
}