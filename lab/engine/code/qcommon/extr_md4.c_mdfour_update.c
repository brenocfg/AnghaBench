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
typedef  int /*<<< orphan*/  uint32_t ;
struct mdfour {int totalN; } ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  copy64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mdfour* m ; 
 int /*<<< orphan*/  mdfour64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdfour_tail (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mdfour_update(struct mdfour *md, byte *in, int n)
{
	uint32_t M[16];

	m = md;

	if (n == 0) mdfour_tail(in, n);

	while (n >= 64) {
		copy64(M, in);
		mdfour64(M);
		in += 64;
		n -= 64;
		m->totalN += 64;
	}

	mdfour_tail(in, n);
}