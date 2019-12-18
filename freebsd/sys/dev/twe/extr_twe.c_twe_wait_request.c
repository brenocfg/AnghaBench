#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct twe_request {scalar_t__ tr_status; TYPE_1__* tr_sc; int /*<<< orphan*/  tr_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  twe_io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIBIO ; 
 scalar_t__ TWE_CMD_BUSY ; 
 scalar_t__ TWE_CMD_COMPLETE ; 
 int /*<<< orphan*/  TWE_CMD_SLEEPER ; 
 int /*<<< orphan*/  TWE_IO_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mtx_sleep (struct twe_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_enqueue_ready (struct twe_request*) ; 
 int /*<<< orphan*/  twe_startio (TYPE_1__*) ; 

__attribute__((used)) static int
twe_wait_request(struct twe_request *tr)
{

    debug_called(4);

    TWE_IO_ASSERT_LOCKED(tr->tr_sc);
    tr->tr_flags |= TWE_CMD_SLEEPER;
    tr->tr_status = TWE_CMD_BUSY;
    twe_enqueue_ready(tr);
    twe_startio(tr->tr_sc);
    while (tr->tr_status == TWE_CMD_BUSY)
	mtx_sleep(tr, &tr->tr_sc->twe_io_lock, PRIBIO, "twewait", 0);
    
    return(tr->tr_status != TWE_CMD_COMPLETE);
}