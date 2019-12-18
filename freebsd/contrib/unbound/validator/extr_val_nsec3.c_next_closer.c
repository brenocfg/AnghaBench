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
 int /*<<< orphan*/  dname_remove_labels (int /*<<< orphan*/ **,size_t*,int) ; 

__attribute__((used)) static void
next_closer(uint8_t* qname, size_t qnamelen, uint8_t* ce, 
	uint8_t** nm, size_t* nmlen)
{
	int strip = dname_count_labels(qname) - dname_count_labels(ce) -1;
	*nm = qname;
	*nmlen = qnamelen;
	if(strip>0)
		dname_remove_labels(nm, nmlen, strip);
}