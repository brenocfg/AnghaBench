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
struct TYPE_2__ {char const* sstr; } ;

/* Variables and functions */
 scalar_t__ STORAGE_MACRO ; 
 TYPE_1__* mstack ; 
 int sp ; 
 scalar_t__* sstack ; 

__attribute__((used)) static int
string_in_use(const char *ptr) 
{
	int i;
	for (i = 0; i <= sp; i++) {
		if (sstack[i] == STORAGE_MACRO && mstack[i].sstr == ptr)
			return 1;
		}
	return 0;
}