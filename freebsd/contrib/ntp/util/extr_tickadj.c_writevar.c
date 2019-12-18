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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  L_SET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
writevar(
	int ofd,
	off_t off,
	int var
	)
{
	
	if (lseek(ofd, off, L_SET) == -1)
	{
		(void) fprintf(stderr, "%s: lseek fails: ", progname);
		perror("");
		exit(1);
	}
	if (write(ofd, (char *)&var, sizeof(int)) != sizeof(int))
	{
		(void) fprintf(stderr, "%s: write fails: ", progname);
		perror("");
		exit(1);
	}
	return;
}