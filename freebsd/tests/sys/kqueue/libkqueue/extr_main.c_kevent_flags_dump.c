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
struct kevent {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_CLEAR ; 
 int /*<<< orphan*/  EV_DELETE ; 
 int /*<<< orphan*/  EV_DISABLE ; 
 int /*<<< orphan*/  EV_DISPATCH ; 
 int /*<<< orphan*/  EV_ENABLE ; 
 int /*<<< orphan*/  EV_EOF ; 
 int /*<<< orphan*/  EV_ERROR ; 
 int /*<<< orphan*/  EV_ONESHOT ; 
 int /*<<< orphan*/  EV_RECEIPT ; 
 int /*<<< orphan*/  KEVFL_DUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 

char *
kevent_flags_dump(struct kevent *kev)
{
    char *buf;

#define KEVFL_DUMP(attrib) \
    if (kev->flags & attrib) \
        strncat(buf, #attrib" ", 64);

    if ((buf = calloc(1, 1024)) == NULL)
        abort();

    snprintf(buf, 1024, "flags = %d (", kev->flags);
    KEVFL_DUMP(EV_ADD);
    KEVFL_DUMP(EV_ENABLE);
    KEVFL_DUMP(EV_DISABLE);
    KEVFL_DUMP(EV_DELETE);
    KEVFL_DUMP(EV_ONESHOT);
    KEVFL_DUMP(EV_CLEAR);
    KEVFL_DUMP(EV_EOF);
    KEVFL_DUMP(EV_ERROR);
#if HAVE_EV_DISPATCH
    KEVFL_DUMP(EV_DISPATCH);
#endif
#if HAVE_EV_RECEIPT
    KEVFL_DUMP(EV_RECEIPT);
#endif
    buf[strlen(buf) - 1] = ')';

    return (buf);
}