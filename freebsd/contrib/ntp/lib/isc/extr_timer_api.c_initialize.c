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
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  createlock ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
initialize(void) {
	RUNTIME_CHECK(isc_mutex_init(&createlock) == ISC_R_SUCCESS);
}