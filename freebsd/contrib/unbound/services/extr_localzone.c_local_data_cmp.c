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
struct local_data {int /*<<< orphan*/  namelabs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int dname_canon_lab_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int 
local_data_cmp(const void* d1, const void* d2)
{
	struct local_data* a = (struct local_data*)d1;
	struct local_data* b = (struct local_data*)d2;
	int m;
	return dname_canon_lab_cmp(a->name, a->namelabs, b->name, 
		b->namelabs, &m);
}