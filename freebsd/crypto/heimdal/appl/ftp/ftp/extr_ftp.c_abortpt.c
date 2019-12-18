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
 scalar_t__ abrtflag ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mflag ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  ptabflg ; 
 int /*<<< orphan*/  ptabort ; 
 int /*<<< orphan*/  stdout ; 

void
abortpt (int sig)
{

    printf ("\n");
    fflush (stdout);
    ptabflg++;
    mflag = 0;
    abrtflag = 0;
    longjmp (ptabort, 1);
}