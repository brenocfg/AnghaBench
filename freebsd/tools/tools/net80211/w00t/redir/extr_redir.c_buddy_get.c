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
struct params {size_t buddy_got; int /*<<< orphan*/ * buddy_data; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  buddy_reset (struct params*) ; 
 int recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int buddy_get(struct params *p, int len)
{
	int rd;

	rd = recv(p->s, &p->buddy_data[p->buddy_got], len, 0);
	if (rd <= 0) {
		buddy_reset(p);
		return 0;
	}

	p->buddy_got += rd;
	return rd == len;
}