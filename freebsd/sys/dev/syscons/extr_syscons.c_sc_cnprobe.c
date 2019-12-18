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
struct consdev {void* cn_pri; int /*<<< orphan*/  cn_name; } ;

/* Variables and functions */
 void* CN_DEAD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VTY_SC ; 
 void* sc_get_cons_priority (int*,int*) ; 
 int /*<<< orphan*/  sckbdprobe (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scvidprobe (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sc_cnprobe(struct consdev *cp)
{
    int unit;
    int flags;

    if (!vty_enabled(VTY_SC)) {
	cp->cn_pri = CN_DEAD;
	return;
    }

    cp->cn_pri = sc_get_cons_priority(&unit, &flags);

    /* a video card is always required */
    if (!scvidprobe(unit, flags, TRUE))
	cp->cn_pri = CN_DEAD;

    /* syscons will become console even when there is no keyboard */
    sckbdprobe(unit, flags, TRUE);

    if (cp->cn_pri == CN_DEAD)
	return;

    /* initialize required fields */
    strcpy(cp->cn_name, "ttyv0");
}