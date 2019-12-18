#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  max_qcount; int /*<<< orphan*/  call_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_qcount; int /*<<< orphan*/  call_count; } ;
struct TYPE_8__ {TYPE_6__ aux; TYPE_1__ kbd; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBDD_DELAYTIME ; 
 int KBDS_AUX_BUFFER_FULL ; 
 int KBDS_BUFFER_FULL ; 
 int KBDS_KBD_BUFFER_FULL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  addq (TYPE_6__*,int) ; 
 scalar_t__ availq (TYPE_1__*) ; 
 int call ; 
 TYPE_2__* kbdcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_data (TYPE_2__*) ; 
 int read_status (TYPE_2__*) ; 
 int removeq (TYPE_1__*) ; 

int
read_kbd_data_no_wait(KBDC p)
{
    int f;

#if KBDIO_DEBUG >= 2
    if (++call > 2000) {
	call = 0;
	log(LOG_DEBUG, "kbdc: kbd q: %d calls, max %d chars, "
			     "aux q: %d calls, max %d chars\n",
		       kbdcp(p)->kbd.call_count, kbdcp(p)->kbd.max_qcount,
		       kbdcp(p)->aux.call_count, kbdcp(p)->aux.max_qcount);
    }
#endif

    if (availq(&kbdcp(p)->kbd)) 
        return removeq(&kbdcp(p)->kbd);
    f = read_status(kbdcp(p)) & KBDS_BUFFER_FULL;
    if (f == KBDS_AUX_BUFFER_FULL) {
        DELAY(KBDD_DELAYTIME);
        addq(&kbdcp(p)->aux, read_data(kbdcp(p)));
        f = read_status(kbdcp(p)) & KBDS_BUFFER_FULL;
    }
    if (f == KBDS_KBD_BUFFER_FULL) {
        DELAY(KBDD_DELAYTIME);
        return read_data(kbdcp(p));
    }
    return -1;		/* no data */
}