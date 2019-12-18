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
struct inoinfo {scalar_t__ i_parent; scalar_t__ i_number; } ;
struct TYPE_2__ {scalar_t__ ino_state; } ;

/* Variables and functions */
 scalar_t__ DFOUND ; 
 scalar_t__ INO_IS_DUNFOUND (scalar_t__) ; 
 TYPE_1__* inoinfo (scalar_t__) ; 
 size_t inplast ; 
 struct inoinfo** inpsort ; 

void
propagate(void)
{
	struct inoinfo **inpp, *inp;
	struct inoinfo **inpend;
	long change;

	inpend = &inpsort[inplast];
	do {
		change = 0;
		for (inpp = inpsort; inpp < inpend; inpp++) {
			inp = *inpp;
			if (inp->i_parent == 0)
				continue;
			if (inoinfo(inp->i_parent)->ino_state == DFOUND &&
			    INO_IS_DUNFOUND(inp->i_number)) {
				inoinfo(inp->i_number)->ino_state = DFOUND;
				change++;
			}
		}
	} while (change > 0);
}