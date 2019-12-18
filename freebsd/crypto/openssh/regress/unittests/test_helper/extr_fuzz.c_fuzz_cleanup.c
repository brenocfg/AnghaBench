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
struct fuzz {struct fuzz* fuzzed; struct fuzz* seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_DBG (char*) ; 
 int /*<<< orphan*/  SIGINFO ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fuzz*) ; 
 int /*<<< orphan*/ * last_fuzz ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fuzz_cleanup(struct fuzz *fuzz)
{
	FUZZ_DBG(("cleanup, fuzz = %p", fuzz));
#ifdef SIGINFO
	last_fuzz = NULL;
	signal(SIGINFO, SIG_DFL);
#endif
	assert(fuzz != NULL);
	assert(fuzz->seed != NULL);
	assert(fuzz->fuzzed != NULL);
	free(fuzz->seed);
	free(fuzz->fuzzed);
	free(fuzz);
}