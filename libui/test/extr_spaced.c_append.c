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
struct thing {void* ptr; int type; } ;

/* Variables and functions */
 int cap ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ grow ; 
 int len ; 
 scalar_t__ realloc (struct thing*,int) ; 
 struct thing* things ; 

__attribute__((used)) static void *append(void *thing, int type)
{
	if (len >= cap) {
		cap += grow;
		things = (struct thing *) realloc(things, cap * sizeof (struct thing));
		if (things == NULL)
			die("reallocating things array in test/spaced.c append()");
	}
	things[len].ptr = thing;
	things[len].type = type;
	len++;
	return things[len - 1].ptr;
}