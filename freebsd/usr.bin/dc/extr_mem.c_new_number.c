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
struct number {int /*<<< orphan*/ * number; scalar_t__ scale; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_new () ; 
 struct number* bmalloc (int) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 

struct number *
new_number(void)
{
	struct number *n;

	n = bmalloc(sizeof(*n));
	n->scale = 0;
	n->number = BN_new();
	if (n->number == NULL)
		err(1, NULL);
	return (n);
}