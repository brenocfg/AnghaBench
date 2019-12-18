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
 int /*<<< orphan*/  key_call_destroy ; 
 int /*<<< orphan*/  key_call_key ; 
 int /*<<< orphan*/  key_call_key_error ; 
 int /*<<< orphan*/  thr_keycreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
key_call_init(void)
{

	key_call_key_error = thr_keycreate(&key_call_key, key_call_destroy);
}