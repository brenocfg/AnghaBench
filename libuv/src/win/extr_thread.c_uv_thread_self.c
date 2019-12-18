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
typedef  int /*<<< orphan*/  uv_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__current_thread_init_guard ; 
 int /*<<< orphan*/  uv__current_thread_key ; 
 int /*<<< orphan*/  uv__init_current_thread_key ; 
 int /*<<< orphan*/  uv_key_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uv_thread_t uv_thread_self(void) {
  uv_once(&uv__current_thread_init_guard, uv__init_current_thread_key);
  return (uv_thread_t) uv_key_get(&uv__current_thread_key);
}