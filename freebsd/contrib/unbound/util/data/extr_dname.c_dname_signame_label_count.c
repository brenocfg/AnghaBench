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
typedef  int uint8_t ;

/* Variables and functions */

int 
dname_signame_label_count(uint8_t* dname)
{
	uint8_t lablen;
	int count = 0;
	if(!*dname)
		return 0;
	if(dname[0] == 1 && dname[1] == '*')
		dname += 2;
	lablen = dname[0];
	while(lablen) {
		count++;
		dname += lablen;
		dname += 1;
		lablen = dname[0];
	}
	return count;
}