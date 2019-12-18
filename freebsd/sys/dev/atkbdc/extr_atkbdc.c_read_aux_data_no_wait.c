#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kbd; int /*<<< orphan*/  aux; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBDD_DELAYTIME ; 
 int KBDS_AUX_BUFFER_FULL ; 
 int KBDS_BUFFER_FULL ; 
 int KBDS_KBD_BUFFER_FULL ; 
 int /*<<< orphan*/  addq (int /*<<< orphan*/ *,int) ; 
 scalar_t__ availq (int /*<<< orphan*/ *) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int read_data (TYPE_1__*) ; 
 int read_status (TYPE_1__*) ; 
 int removeq (int /*<<< orphan*/ *) ; 

int
read_aux_data_no_wait(KBDC p)
{
    int f;

    if (availq(&kbdcp(p)->aux)) 
        return removeq(&kbdcp(p)->aux);
    f = read_status(kbdcp(p)) & KBDS_BUFFER_FULL;
    if (f == KBDS_KBD_BUFFER_FULL) {
        DELAY(KBDD_DELAYTIME);
        addq(&kbdcp(p)->kbd, read_data(kbdcp(p)));
        f = read_status(kbdcp(p)) & KBDS_BUFFER_FULL;
    }
    if (f == KBDS_AUX_BUFFER_FULL) {
        DELAY(KBDD_DELAYTIME);
        return read_data(kbdcp(p));
    }
    return -1;		/* no data */
}