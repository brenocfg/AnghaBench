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
 unsigned int CKSEG0 ; 
 int /*<<< orphan*/  ERRCTL_SPRAM ; 
 int /*<<< orphan*/  Index_Store_Tag_I ; 
 unsigned int bis_c0_errctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ehb () ; 
 int /*<<< orphan*/  write_c0_errctl (unsigned int) ; 
 int /*<<< orphan*/  write_c0_taglo (unsigned int) ; 

__attribute__((used)) static void ispram_store_tag(unsigned int offset, unsigned int data)
{
	unsigned int errctl;

	/* enable SPRAM tag access */
	errctl = bis_c0_errctl(ERRCTL_SPRAM);
	ehb();

	write_c0_taglo(data);
	ehb();

	cache_op(Index_Store_Tag_I, CKSEG0|offset);
	ehb();

	write_c0_errctl(errctl);
	ehb();
}