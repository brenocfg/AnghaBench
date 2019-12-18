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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ collsym_t ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
collsym_compare(const void *n1, const void *n2)
{
	const collsym_t *c1 = n1;
	const collsym_t *c2 = n2;
	int rv;

	rv = strcmp(c1->name, c2->name);
	return ((rv < 0) ? -1 : (rv > 0) ? 1 : 0);
}