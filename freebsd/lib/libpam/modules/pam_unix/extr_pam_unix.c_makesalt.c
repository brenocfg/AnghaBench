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

/* Variables and functions */
 int SALTSIZE ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  to64 (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
makesalt(char salt[SALTSIZE + 1])
{
	int i;

	/* These are not really random numbers, they are just
	 * numbers that change to thwart construction of a
	 * dictionary.
	 */
	for (i = 0; i < SALTSIZE; i += 4)
		to64(&salt[i], arc4random(), 4);
	salt[SALTSIZE] = '\0';
}