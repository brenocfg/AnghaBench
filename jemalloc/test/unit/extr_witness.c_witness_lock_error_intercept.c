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
typedef  int /*<<< orphan*/  witness_t ;
typedef  int /*<<< orphan*/  witness_list_t ;

/* Variables and functions */
 int saw_lock_error ; 

__attribute__((used)) static void
witness_lock_error_intercept(const witness_list_t *witnesses,
    const witness_t *witness) {
	saw_lock_error = true;
}