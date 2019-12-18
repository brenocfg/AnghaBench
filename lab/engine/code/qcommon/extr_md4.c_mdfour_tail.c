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
typedef  int uint32_t ;
typedef  int byte ;
struct TYPE_2__ {int totalN; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  Com_Memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy4 (int*,int) ; 
 int /*<<< orphan*/  copy64 (int*,int*) ; 
 TYPE_1__* m ; 
 int /*<<< orphan*/  mdfour64 (int*) ; 

__attribute__((used)) static void mdfour_tail(byte *in, int n)
{
	byte buf[128];
	uint32_t M[16];
	uint32_t b;

	m->totalN += n;

	b = m->totalN * 8;

	Com_Memset(buf, 0, 128);
	if (n) Com_Memcpy(buf, in, n);
	buf[n] = 0x80;

	if (n <= 55) {
		copy4(buf+56, b);
		copy64(M, buf);
		mdfour64(M);
	} else {
		copy4(buf+120, b);
		copy64(M, buf);
		mdfour64(M);
		copy64(M, buf+64);
		mdfour64(M);
	}
}