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
 int errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (char const*,int) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
skip_over(FILE *fp, const char *cs)
{
	int c;

	c = getc(fp);
	while (c != EOF && strchr(cs, c) != NULL)
		c = getc(fp);
	if (c != EOF) {
		ungetc(c, fp);
		return (0);
	}
	return (ferror(fp) ? errno : -1);
}