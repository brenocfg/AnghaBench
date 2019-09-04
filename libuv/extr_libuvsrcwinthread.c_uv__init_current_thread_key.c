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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  uv__current_thread_key ; 
 scalar_t__ uv_key_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__init_current_thread_key(void) {
  if (uv_key_create(&uv__current_thread_key))
    abort();
}