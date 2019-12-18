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
struct cidr {scalar_t__ prefix; } ;

/* Variables and functions */
 scalar_t__ printed ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

__attribute__((used)) static bool cidr_howmany(struct cidr *a, struct cidr *b)
{
	if (printed)
		qprintf(" ");

	if (b->prefix < a->prefix)
		qprintf("0");
	else
		qprintf("%u", 1 << (b->prefix - a->prefix));

	return true;
}