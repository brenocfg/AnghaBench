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
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ VALID_HASH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hash ; 
 int /*<<< orphan*/  isc_hash_ctxinit (int /*<<< orphan*/ *) ; 

void
isc_hash_init() {
	INSIST(hash != NULL && VALID_HASH(hash));

	isc_hash_ctxinit(hash);
}