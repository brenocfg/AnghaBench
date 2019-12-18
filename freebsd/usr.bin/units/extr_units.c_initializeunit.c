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
struct unittype {double factor; double offset; scalar_t__ quantity; int /*<<< orphan*/ ** denominator; int /*<<< orphan*/ * numerator; } ;

/* Variables and functions */

__attribute__((used)) static void 
initializeunit(struct unittype * theunit)
{
	theunit->numerator[0] = theunit->denominator[0] = NULL;
	theunit->factor = 1.0;
	theunit->offset = 0.0;
	theunit->quantity = 0;
}