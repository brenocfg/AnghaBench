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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ motdinterrupt ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigint ; 

__attribute__((used)) static int
motd(const char *motdfile)
{
	struct sigaction newint, oldint;
	FILE *f;
	int ch;

	if ((f = fopen(motdfile, "r")) == NULL)
		return (-1);
	motdinterrupt = 0;
	newint.sa_handler = sigint;
	newint.sa_flags = 0;
	sigfillset(&newint.sa_mask);
	sigaction(SIGINT, &newint, &oldint);
	while ((ch = fgetc(f)) != EOF && !motdinterrupt)
		putchar(ch);
	sigaction(SIGINT, &oldint, NULL);
	if (ch != EOF || ferror(f)) {
		fclose(f);
		return (-1);
	}
	fclose(f);
	return (0);
}