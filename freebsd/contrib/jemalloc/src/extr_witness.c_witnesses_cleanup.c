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
typedef  int /*<<< orphan*/  witness_tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  witness_assert_lockless (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  witness_tsd_tsdn (int /*<<< orphan*/ *) ; 

void
witnesses_cleanup(witness_tsd_t *witness_tsd) {
	witness_assert_lockless(witness_tsd_tsdn(witness_tsd));

	/* Do nothing. */
}