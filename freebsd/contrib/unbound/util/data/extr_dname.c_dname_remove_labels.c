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
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 

void 
dname_remove_labels(uint8_t** dname, size_t* len, int n)
{
	int i;
	for(i=0; i<n; i++)
		dname_remove_label(dname, len);
}