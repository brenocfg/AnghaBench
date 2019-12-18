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
 int /*<<< orphan*/  Decimal (char*,int,int,int /*<<< orphan*/ ) ; 
 int dos_cyls ; 
 int dos_cylsecs ; 
 int dos_heads ; 
 int dos_sectors ; 
 scalar_t__ ok (char*) ; 
 int /*<<< orphan*/  print_params () ; 

void
get_params_to_use()
{
	int	tmp;
	print_params();
	if (ok("Do you want to change our idea of what BIOS thinks ?"))
	{
		do
		{
			Decimal("BIOS's idea of #cylinders", dos_cyls, tmp, 0);
			Decimal("BIOS's idea of #heads", dos_heads, tmp, 0);
			Decimal("BIOS's idea of #sectors", dos_sectors, tmp, 0);
			dos_cylsecs = dos_heads * dos_sectors;
			print_params();
		}
		while(!ok("Are you happy with this choice"));
	}
}