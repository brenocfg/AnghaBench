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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ bol ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ isblank (int) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
skipws(FILE *fd)
{
	int c, i;

	i = 0;
	while ((c = getc(fd)) != EOF && isblank(c))
		i++;
	if (c != EOF)
		ungetc(c, fd);
	if (i != 0)
		bol = 0;
	return 0;
}