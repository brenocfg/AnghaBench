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
struct name {struct name* n_blink; struct name* n_flink; } ;

/* Variables and functions */
 struct name* tailof (struct name*) ; 

struct name *
cat(struct name *n1, struct name *n2)
{
	struct name *tail;

	if (n1 == NULL)
		return (n2);
	if (n2 == NULL)
		return (n1);
	tail = tailof(n1);
	tail->n_flink = n2;
	n2->n_blink = tail;
	return (n1);
}