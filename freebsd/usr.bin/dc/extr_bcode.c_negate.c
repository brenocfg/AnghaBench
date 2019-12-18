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
struct number {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_is_negative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ ,int) ; 

void
negate(struct number *n)
{
	BN_set_negative(n->number, !BN_is_negative(n->number));
}