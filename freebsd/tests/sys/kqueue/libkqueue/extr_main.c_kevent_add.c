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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_int ;
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SET (struct kevent*,uintptr_t,short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kevent (int,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* kevent_to_str (struct kevent*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
kevent_add(int kqfd, struct kevent *kev, 
        uintptr_t ident,
        short     filter,
        u_short   flags,
        u_int     fflags,
        intptr_t  data,
        void      *udata)
{
    char *kev_str;
    
    EV_SET(kev, ident, filter, flags, fflags, data, NULL);    
    if (kevent(kqfd, kev, 1, NULL, 0, NULL) < 0) {
        kev_str = kevent_to_str(kev);
        printf("Unable to add the following kevent:\n%s\n",
                kev_str);
        free(kev_str);
        err(1, "kevent(): %s", strerror(errno));
    }
}