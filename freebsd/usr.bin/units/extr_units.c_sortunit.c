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
struct unittype {char** numerator; char** denominator; } ;

/* Variables and functions */
 int /*<<< orphan*/  compare ; 
 int /*<<< orphan*/  qsort (char**,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
sortunit(struct unittype * theunit)
{
	char **ptr;
	unsigned int count;

	for (count = 0, ptr = theunit->numerator; *ptr; ptr++, count++);
	qsort(theunit->numerator, count, sizeof(char *), compare);
	for (count = 0, ptr = theunit->denominator; *ptr; ptr++, count++);
	qsort(theunit->denominator, count, sizeof(char *), compare);
}