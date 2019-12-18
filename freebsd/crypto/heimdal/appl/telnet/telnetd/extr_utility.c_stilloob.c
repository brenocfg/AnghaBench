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
struct timeval {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fatalperror (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ourpty ; 
 int select (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval*) ; 

int
stilloob(int s)
{
    static struct timeval timeout = { 0 };
    fd_set	excepts;
    int value;

    if (s >= FD_SETSIZE)
	fatal(ourpty, "fd too large");

    do {
	FD_ZERO(&excepts);
	FD_SET(s, &excepts);
	value = select(s+1, 0, 0, &excepts, &timeout);
    } while ((value == -1) && (errno == EINTR));

    if (value < 0) {
	fatalperror(ourpty, "select");
    }
    if (FD_ISSET(s, &excepts)) {
	return 1;
    } else {
	return 0;
    }
}