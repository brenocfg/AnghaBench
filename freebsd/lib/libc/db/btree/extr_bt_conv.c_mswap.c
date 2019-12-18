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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  PAGE ;

/* Variables and functions */
 int /*<<< orphan*/  P_32_SWAP (char*) ; 

__attribute__((used)) static void
mswap(PAGE *pg)
{
	char *p;

	p = (char *)pg;
	P_32_SWAP(p);		/* magic */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* version */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* psize */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* free */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* nrecs */
	p += sizeof(u_int32_t);
	P_32_SWAP(p);		/* flags */
	p += sizeof(u_int32_t);
}