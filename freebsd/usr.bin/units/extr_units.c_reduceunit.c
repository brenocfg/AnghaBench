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
 int reduceproduct (struct unittype*,int) ; 

__attribute__((used)) static int 
reduceunit(struct unittype * theunit)
{
	int ret;

	ret = 1;
	while (ret & 1) {
		ret = reduceproduct(theunit, 0) | reduceproduct(theunit, 1);
		if (ret & 4)
			return 1;
	}
	return 0;
}