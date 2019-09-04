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
typedef  int /*<<< orphan*/  Type ;

/* Variables and functions */
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void printtype(Type ty, int fd) {
	static unsigned mark;
	prtype(ty, fd == 1 ? stdout : stderr, 0, ++mark);
	fprint(fd == 1 ? stdout : stderr, "\n");
}