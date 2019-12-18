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
struct unittype {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;

/* Variables and functions */
 scalar_t__ compareproducts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
compareunits(struct unittype * first, struct unittype * second)
{
	return
	compareproducts(first->numerator, second->numerator) ||
	compareproducts(first->denominator, second->denominator);
}