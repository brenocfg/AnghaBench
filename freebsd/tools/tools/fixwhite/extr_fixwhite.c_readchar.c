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
 int EOF ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int getchar () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static char
readchar(void)
{
	int c;

	c = getchar();
	if (c == EOF && ferror(stdin)) {
		perror("read");
		exit(1);
	}
	return (c);
}