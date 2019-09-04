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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  tls_key ; 
 void* uv_key_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_key_set (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void tls_thread(void* arg) {
  ASSERT(NULL == uv_key_get(&tls_key));
  uv_key_set(&tls_key, arg);
  ASSERT(arg == uv_key_get(&tls_key));
  uv_key_set(&tls_key, NULL);
  ASSERT(NULL == uv_key_get(&tls_key));
}