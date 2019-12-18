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
struct number {int /*<<< orphan*/  number; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_dup (int /*<<< orphan*/ ) ; 
 struct number* bmalloc (int) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ ) ; 

struct number *
dup_number(const struct number *a)
{
	struct number *n;

	n = bmalloc(sizeof(*n));
	n->scale = a->scale;
	n->number = BN_dup(a->number);
	bn_checkp(n->number);
	return (n);
}