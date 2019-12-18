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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  ExitProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TTY (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 scalar_t__ can_restore ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  original ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
exit_error(void)
{
    if (can_restore)
	SET_TTY(STDERR_FILENO, &original);
    (void) fprintf(stderr, "\n");
    fflush(stderr);
    ExitProgram(EXIT_FAILURE);
    /* NOTREACHED */
}