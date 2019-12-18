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
struct TYPE_2__ {void* va_token; } ;

/* Variables and functions */
 TYPE_1__** adapter ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int vid_find_adapter (char*,int) ; 

int
vid_allocate(char *driver, int unit, void *id)
{
	int index;
	int s;

	s = spltty();
	index = vid_find_adapter(driver, unit);
	if (index >= 0) {
		if (adapter[index]->va_token) {
			splx(s);
			return -1;
		}
		adapter[index]->va_token = id;
	}
	splx(s);
	return index;
}