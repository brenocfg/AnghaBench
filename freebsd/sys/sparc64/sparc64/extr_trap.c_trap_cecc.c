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
typedef  int u_long ;

/* Variables and functions */
 int AA_ESTATE_CEEN ; 
 int AA_ESTATE_NCEEN ; 
 int /*<<< orphan*/  ASI_AFSR ; 
 int /*<<< orphan*/  ASI_ESTATE_ERROR_EN_REG ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_flush () ; 
 int /*<<< orphan*/  corrected_ecc ; 
 int /*<<< orphan*/  impl ; 
 int ldxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stxa_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
trap_cecc(void)
{
	u_long eee;

	/*
	 * Turn off (non-)correctable error reporting while we're dealing
	 * with the error.
	 */
	eee = ldxa(0, ASI_ESTATE_ERROR_EN_REG);
	stxa_sync(0, ASI_ESTATE_ERROR_EN_REG, eee & ~(AA_ESTATE_NCEEN |
	    AA_ESTATE_CEEN));
	/* Flush the caches in order ensure no corrupt data got installed. */
	cache_flush();
	/* Ensure the caches are still turned on (should be). */
	cache_enable(PCPU_GET(impl));
	/* Clear the error from the AFSR. */
	stxa_sync(0, ASI_AFSR, ldxa(0, ASI_AFSR));
	corrected_ecc++;
	printf("corrected ECC error\n");
	/* Turn (non-)correctable error reporting back on. */
	stxa_sync(0, ASI_ESTATE_ERROR_EN_REG, eee);
	return (0);
}