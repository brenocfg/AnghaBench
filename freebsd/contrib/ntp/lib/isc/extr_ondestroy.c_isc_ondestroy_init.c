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
struct TYPE_3__ {int /*<<< orphan*/  events; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ isc_ondestroy_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ONDESTROY_MAGIC ; 

void
isc_ondestroy_init(isc_ondestroy_t *ondest) {
	ondest->magic = ONDESTROY_MAGIC;
	ISC_LIST_INIT(ondest->events);
}