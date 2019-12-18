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
 int /*<<< orphan*/  A_STANDOUT ; 
 int /*<<< orphan*/  COLOR_PAIR (int) ; 
 int /*<<< orphan*/  attroff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attron (int /*<<< orphan*/ ) ; 
 scalar_t__ hascolor ; 

__attribute__((used)) static void
standt(int on)
{
	if (on) {
		if(hascolor) {
			attron(COLOR_PAIR(1));
		} else {
			attron(A_STANDOUT);
		}
	} else {
		if(hascolor) {
			attron(COLOR_PAIR(2));
		} else {
			attroff(A_STANDOUT);
		}
	}
}