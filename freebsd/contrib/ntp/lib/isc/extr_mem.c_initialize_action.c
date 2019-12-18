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

/* Variables and functions */
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  contexts ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock ; 
 scalar_t__ totallost ; 

__attribute__((used)) static void
initialize_action(void) {
	RUNTIME_CHECK(isc_mutex_init(&lock) == ISC_R_SUCCESS);
	ISC_LIST_INIT(contexts);
	totallost = 0;
}