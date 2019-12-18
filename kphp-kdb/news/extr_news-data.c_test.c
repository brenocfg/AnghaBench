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

/* Variables and functions */
 int /*<<< orphan*/  PACK_BOOKMARK (long long,int,int,int) ; 
 int /*<<< orphan*/  UNPACK_BOOKMARK (long long,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

void test (int a, int b, int c) {
	int _a, _b, _c;
	long long x;
	PACK_BOOKMARK(x,a,b,c);
	UNPACK_BOOKMARK(x,_a,_b,_c);
	assert (a == _a && b == _b && c == _c);
}