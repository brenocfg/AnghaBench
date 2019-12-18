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
typedef  scalar_t__ u_int ;
struct number {scalar_t__ scale; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  scale_number (int /*<<< orphan*/ ,scalar_t__) ; 

void
normalize(struct number *n, u_int s)
{

	scale_number(n->number, s - n->scale);
	n->scale = s;
}