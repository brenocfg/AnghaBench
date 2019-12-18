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
 int /*<<< orphan*/  bcache_add_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdinfo ; 
 int /*<<< orphan*/  efiblk_pdinfo_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efipart_updatecd () ; 

__attribute__((used)) static int
efipart_initcd(void)
{
	efipart_updatecd();

	bcache_add_dev(efiblk_pdinfo_count(&cdinfo));
	return (0);
}