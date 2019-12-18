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
 int dname_canon_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 

int
dname_canonical_compare(uint8_t* d1, uint8_t* d2)
{
	int labs1, labs2, m;
	labs1 = dname_count_labels(d1);
	labs2 = dname_count_labels(d2);
	return dname_canon_lab_cmp(d1, labs1, d2, labs2, &m);
}