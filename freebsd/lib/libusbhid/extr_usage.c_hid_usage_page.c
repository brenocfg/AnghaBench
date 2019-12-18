#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int usage; char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int npages ; 
 TYPE_1__* pages ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
hid_usage_page(int i)
{
	static char b[10];
	int k;

	if (!pages)
		errx(1, "no hid table");

	for (k = 0; k < npages; k++)
		if (pages[k].usage == i)
			return pages[k].name;
	sprintf(b, "0x%04x", i);
	return b;
}