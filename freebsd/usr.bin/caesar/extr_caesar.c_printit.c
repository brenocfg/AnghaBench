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
 int /*<<< orphan*/  ROTATE (int,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getchar () ; 
 int /*<<< orphan*/  putchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
printit(char *arg)
{
	int ch, rot;

	if ((rot = atoi(arg)) < 0) {
		(void)fprintf(stderr, "caesar: bad rotation value.\n");
		exit(1);
	}
	while ((ch = getchar()) != EOF)
		putchar(ROTATE(ch, rot));
	exit(0);
}