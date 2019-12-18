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
struct twe_request {int /*<<< orphan*/  tr_sc; int /*<<< orphan*/ * tr_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_IO_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  dumping ; 
 int /*<<< orphan*/  twe_enqueue_free (struct twe_request*) ; 
 int /*<<< orphan*/  twe_panic (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
twe_release_request(struct twe_request *tr)
{
    debug_called(4);

    if (!dumping)
	TWE_IO_ASSERT_LOCKED(tr->tr_sc);
    if (tr->tr_private != NULL)
	twe_panic(tr->tr_sc, "tr_private != NULL");
    twe_enqueue_free(tr);
}