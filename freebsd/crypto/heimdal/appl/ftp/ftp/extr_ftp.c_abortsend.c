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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 scalar_t__ abrtflag ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mflag ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sendabort ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static RETSIGTYPE
abortsend (int sig)
{

    mflag = 0;
    abrtflag = 0;
    printf ("\nsend aborted\nwaiting for remote to finish abort\n");
    fflush (stdout);
    longjmp (sendabort, 1);
}