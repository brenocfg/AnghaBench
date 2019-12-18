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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/ * mpfps_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  PTOV (int) ; 
 int /*<<< orphan*/ * biosmptable_search_mpfps (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memread (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static mpfps_t
biosmptable_find_mpfps(void)
{
    mpfps_t mpfps;
    uint16_t addr;

    /* EBDA is the 1 KB addressed by the 16 bit pointer at 0x40E. */
    if (!memread(PTOV(0x40E), &addr, sizeof(addr)))
	return (NULL);
    mpfps = biosmptable_search_mpfps(PTOV(addr << 4), 0x400);
    if (mpfps != NULL)
	return (mpfps);

    /* Check the BIOS. */
    mpfps = biosmptable_search_mpfps(PTOV(0xf0000), 0x10000);
    if (mpfps != NULL)
	return (mpfps);

    return (NULL);
}