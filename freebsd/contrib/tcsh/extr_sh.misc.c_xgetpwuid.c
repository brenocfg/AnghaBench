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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 scalar_t__ handle_pending_signals () ; 

struct passwd *
xgetpwuid(uid_t xuid)
{
    struct passwd *res;

    errno = 0;
    while ((res = getpwuid(xuid)) == NULL && errno == EINTR) {
	if (handle_pending_signals())
	    break;
	errno = 0;
    }
    return res;
}