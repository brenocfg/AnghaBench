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
struct kevent {int dummy; } ;

/* Variables and functions */
 struct kevent* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int kevent (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *) ; 

struct kevent *
kevent_get(int kqfd)
{
    int nfds;
    struct kevent *kev;

    if ((kev = calloc(1, sizeof(*kev))) == NULL)
        err(1, "out of memory");
    
    nfds = kevent(kqfd, NULL, 0, kev, 1, NULL);
    if (nfds < 1)
        err(1, "kevent(2)");

    return (kev);
}