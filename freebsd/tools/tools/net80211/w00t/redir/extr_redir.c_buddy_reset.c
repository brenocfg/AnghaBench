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
struct params {scalar_t__ buddy_got; } ;

/* Variables and functions */
 int connect_buddy (struct params*) ; 
 int /*<<< orphan*/  err (int,char*) ; 

void buddy_reset(struct params *p)
{
	p->buddy_got = 0;

	if (connect_buddy(p) == -1)
		err(1, "connect_buddy()");
}