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
 int /*<<< orphan*/  Bzero (char*,int) ; 
 char* addmask_key ; 
 int /*<<< orphan*/  mask_rnhead ; 
 int max_keylen ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rn_inithead (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* rn_ones ; 
 char* rn_zeros ; 
 scalar_t__ rtmalloc (int,char*) ; 

void
rn_init(void)
{
	char *cp, *cplim;
	if (max_keylen == 0) {
		printf("rn_init: radix functions require max_keylen be set\n");
		return;
	}
	rn_zeros = (char *)rtmalloc(3 * max_keylen, "rn_init");
	Bzero(rn_zeros, 3 * max_keylen);
	rn_ones = cp = rn_zeros + max_keylen;
	addmask_key = cplim = rn_ones + max_keylen;
	while (cp < cplim)
		*cp++ = -1;
	if (rn_inithead(&mask_rnhead, 0) == 0)
		panic("rn_init 2");
}