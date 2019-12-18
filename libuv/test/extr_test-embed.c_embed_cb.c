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
typedef  int /*<<< orphan*/  uv_async_t ;

/* Variables and functions */
 int /*<<< orphan*/  UV_RUN_ONCE ; 
 int /*<<< orphan*/  embed_sem ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void embed_cb(uv_async_t* async) {
  uv_run(uv_default_loop(), UV_RUN_ONCE);

  uv_sem_post(&embed_sem);
}