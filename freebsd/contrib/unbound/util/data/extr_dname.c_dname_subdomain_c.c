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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 scalar_t__ dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 

int 
dname_subdomain_c(uint8_t* d1, uint8_t* d2)
{
	int m;
	/* check subdomain: d1: www.example.com. and d2: example.com. */
	/*  	or 	    d1: example.com. and d2: example.com. */
	int labs1 = dname_count_labels(d1);
	int labs2 = dname_count_labels(d2);
	if(labs2 > labs1) 
		return 0;
	if(dname_lab_cmp(d1, labs1, d2, labs2, &m) < 0) {
		/* must have been example.com , www.example.com - wrong */
		/* or otherwise different dnames */
		return 0;
	}
	return (m == labs2);
}