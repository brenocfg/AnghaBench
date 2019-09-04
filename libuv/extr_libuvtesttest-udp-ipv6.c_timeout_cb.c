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
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timeout_cb(uv_timer_t* timer) {
  uv_close((uv_handle_t*)&server, close_cb);
  uv_close((uv_handle_t*)&client, close_cb);
  uv_close((uv_handle_t*)&timeout, close_cb);
}