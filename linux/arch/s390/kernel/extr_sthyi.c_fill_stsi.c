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
struct sthyi_sctns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_stsi_mac (struct sthyi_sctns*,void*) ; 
 int /*<<< orphan*/  fill_stsi_par (struct sthyi_sctns*,void*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_stsi(struct sthyi_sctns *sctns)
{
	void *sysinfo;

	/* Errors are handled through the validity bits in the response. */
	sysinfo = (void *)__get_free_page(GFP_KERNEL);
	if (!sysinfo)
		return;

	fill_stsi_mac(sctns, sysinfo);
	fill_stsi_par(sctns, sysinfo);

	free_pages((unsigned long)sysinfo, 0);
}