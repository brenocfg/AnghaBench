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
typedef  int u32 ;

/* Variables and functions */
 int ROLc (int,int) ; 
 int RORc (int,int) ; 
 int* SP1 ; 
 int* SP2 ; 
 int* SP3 ; 
 int* SP4 ; 
 int* SP5 ; 
 int* SP6 ; 
 int* SP7 ; 
 int* SP8 ; 

__attribute__((used)) static void desfunc(u32 *block, const u32 *keys)
{
	u32 work, right, leftt;
	int cur_round;

	leftt = block[0];
	right = block[1];

	work = ((leftt >> 4)  ^ right) & 0x0f0f0f0fL;
	right ^= work;
	leftt ^= (work << 4);

	work = ((leftt >> 16) ^ right) & 0x0000ffffL;
	right ^= work;
	leftt ^= (work << 16);

	work = ((right >> 2)  ^ leftt) & 0x33333333L;
	leftt ^= work;
	right ^= (work << 2);

	work = ((right >> 8)  ^ leftt) & 0x00ff00ffL;
	leftt ^= work;
	right ^= (work << 8);

	right = ROLc(right, 1);
	work = (leftt ^ right) & 0xaaaaaaaaL;

	leftt ^= work;
	right ^= work;
	leftt = ROLc(leftt, 1);

	for (cur_round = 0; cur_round < 8; cur_round++) {
		work  = RORc(right, 4) ^ *keys++;
		leftt ^= SP7[work        & 0x3fL]
			^ SP5[(work >>  8) & 0x3fL]
			^ SP3[(work >> 16) & 0x3fL]
			^ SP1[(work >> 24) & 0x3fL];
		work  = right ^ *keys++;
		leftt ^= SP8[ work        & 0x3fL]
			^  SP6[(work >>  8) & 0x3fL]
			^  SP4[(work >> 16) & 0x3fL]
			^  SP2[(work >> 24) & 0x3fL];

		work = RORc(leftt, 4) ^ *keys++;
		right ^= SP7[ work        & 0x3fL]
			^  SP5[(work >>  8) & 0x3fL]
			^  SP3[(work >> 16) & 0x3fL]
			^  SP1[(work >> 24) & 0x3fL];
		work  = leftt ^ *keys++;
		right ^= SP8[ work        & 0x3fL]
			^  SP6[(work >>  8) & 0x3fL]
			^  SP4[(work >> 16) & 0x3fL]
			^  SP2[(work >> 24) & 0x3fL];
	}

	right = RORc(right, 1);
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = RORc(leftt, 1);
	work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
	right ^= work;
	leftt ^= (work << 8);
	/* -- */
	work = ((leftt >> 2) ^ right) & 0x33333333L;
	right ^= work;
	leftt ^= (work << 2);
	work = ((right >> 16) ^ leftt) & 0x0000ffffL;
	leftt ^= work;
	right ^= (work << 16);
	work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
	leftt ^= work;
	right ^= (work << 4);

	block[0] = right;
	block[1] = leftt;
}