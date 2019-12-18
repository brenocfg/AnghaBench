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
 int CHILDEXIT ; 
 long FROBVAL ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 long getpid () ; 
 long getppid () ; 
 long labs (long) ; 
 int /*<<< orphan*/  printf (char*,long**,long*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
clone_func(void *arg)
{
	long *frobp = arg, diff;

	printf("child: stack ~= %p, frobme = %p\n", &frobp, frobp);
	fflush(stdout);

	if (frobp[0] != getppid())
		return 1;

	if (frobp[0] == getpid())
		return 2;

	diff = labs(frobp[1] - (long) &frobp);

	if (diff > 1024)
		return 3;

	frobp[1] = FROBVAL;

	return (CHILDEXIT);
}