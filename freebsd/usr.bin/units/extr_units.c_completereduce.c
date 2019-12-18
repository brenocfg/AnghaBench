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
struct unittype {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancelunit (struct unittype*) ; 
 scalar_t__ reduceunit (struct unittype*) ; 
 int /*<<< orphan*/  sortunit (struct unittype*) ; 

__attribute__((used)) static int 
completereduce(struct unittype * unit)
{
	if (reduceunit(unit))
		return 1;
	sortunit(unit);
	cancelunit(unit);
	return 0;
}