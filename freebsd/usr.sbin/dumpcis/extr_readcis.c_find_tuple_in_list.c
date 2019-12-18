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
struct tuple_list {struct tuple* tuples; } ;
struct tuple {unsigned char code; struct tuple* next; } ;

/* Variables and functions */

__attribute__((used)) static struct tuple *
find_tuple_in_list(struct tuple_list *tl, unsigned char code)
{
	struct tuple *tp;

	for (tp = tl->tuples; tp; tp = tp->next)
		if (tp->code == code)
			break;
	return (tp);
}