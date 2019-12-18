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
typedef  int /*<<< orphan*/  timeo ;
struct timespec {int dummy; } ;
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,struct timespec*) ; 
 char* kevent_to_str (struct kevent*) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  memset (struct timespec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  puts (char*) ; 

void 
test_no_kevents_quietly(void)
{
    int nfds;
    struct timespec timeo;
    struct kevent kev;
    char *kev_str;

    memset(&timeo, 0, sizeof(timeo));
    nfds = kevent(kqfd, NULL, 0, &kev, 1, &timeo);
    if (nfds != 0) {
        puts("\nUnexpected event:");
        kev_str = kevent_to_str(&kev);
        puts(kev_str);
        free(kev_str);
        errx(1, "%d event(s) pending, but none expected:", nfds);
    }
}