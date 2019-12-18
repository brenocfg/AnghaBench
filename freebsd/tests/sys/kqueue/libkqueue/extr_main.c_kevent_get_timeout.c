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
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;
struct kevent {int dummy; } ;

/* Variables and functions */
 struct kevent* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct kevent*) ; 
 int kevent (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,struct timespec*) ; 

struct kevent *
kevent_get_timeout(int kqfd, int seconds)
{
    int nfds;
    struct kevent *kev;
    struct timespec timeout = {seconds, 0};

    if ((kev = calloc(1, sizeof(*kev))) == NULL)
        err(1, "out of memory");
    
    nfds = kevent(kqfd, NULL, 0, kev, 1, &timeout);
    if (nfds < 0) {
        err(1, "kevent(2)");
    } else if (nfds == 0) {
        free(kev);
        kev = NULL;
    }

    return (kev);
}