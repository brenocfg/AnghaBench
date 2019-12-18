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
 int MAX_CHECK ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
istextfile(FILE *f)
{
	int	ch, i;

	if (f == NULL)
		return (1);
	rewind(f);
	for (i = 0; i <= MAX_CHECK; i++) {
		ch = fgetc(f);
		if (ch == '\0') {
			rewind(f);
			return (0);
		}
		if (ch == EOF)
			break;
	}
	rewind(f);
	return (1);
}