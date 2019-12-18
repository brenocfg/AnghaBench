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
typedef  int /*<<< orphan*/  uintmax_t ;
struct kevent {scalar_t__* ext; int /*<<< orphan*/  udata; scalar_t__ data; int /*<<< orphan*/  filter; scalar_t__ ident; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* kevent_fflags_dump (struct kevent*) ; 
 char* kevent_flags_dump (struct kevent*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

char *
kevent_to_str(struct kevent *kev)
{
    char buf[512];
    char *flags_str = kevent_flags_dump(kev);
    char *fflags_str = kevent_fflags_dump(kev);

    snprintf(&buf[0], sizeof(buf), 
            "[ident=%ju, filter=%d, %s, %s, data=%jd, udata=%p, "
            "ext=[%jx %jx %jx %jx]",
            (uintmax_t) kev->ident,
            kev->filter,
            flags_str,
            fflags_str,
            (uintmax_t)kev->data,
            kev->udata,
            (uintmax_t)kev->ext[0],
            (uintmax_t)kev->ext[1],
            (uintmax_t)kev->ext[2],
            (uintmax_t)kev->ext[3]);

    free(flags_str);
    free(fflags_str);
    
    return (strdup(buf));
}