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
 int /*<<< orphan*/  NSWAP ; 
 int /*<<< orphan*/  blocksize ; 
 int /*<<< orphan*/  calclens () ; 
 int /*<<< orphan*/  dlen ; 
 int /*<<< orphan*/  dsinit (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  getbsize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  header ; 
 int /*<<< orphan*/  hlen ; 
 int /*<<< orphan*/  kd ; 
 int /*<<< orphan*/  kvm_getswapinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmsw ; 
 int /*<<< orphan*/  kvnsw ; 
 int /*<<< orphan*/  odlen ; 
 int /*<<< orphan*/  okvnsw ; 
 int /*<<< orphan*/  oulen ; 
 int /*<<< orphan*/  pagesize ; 
 int /*<<< orphan*/  ulen ; 

int
initswap(void)
{
	static int once = 0;

	if (once)
		return (1);

	header = getbsize(&hlen, &blocksize);
	pagesize = getpagesize();

	if ((kvnsw = kvm_getswapinfo(kd, kvmsw, NSWAP, 0)) < 0) {
		error("systat: kvm_getswapinfo failed");
		return (0);
	}
	okvnsw = kvnsw;

	calclens();
	odlen = dlen;
	oulen = ulen;

	once = 1;

	dsinit(12);

	return (1);
}