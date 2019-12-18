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
struct range {int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;

/* Variables and functions */
 int /*<<< orphan*/ * last ; 
 int /*<<< orphan*/  prange (struct range*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  skip (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
change(int i, struct range *rold, bool dup)
{

	printf("%d:", i);
	last[i] = rold->to;
	prange(rold);
	if (dup)
		return;
	i--;
	skip(i, rold->from, NULL);
	skip(i, rold->to, "  ");
}