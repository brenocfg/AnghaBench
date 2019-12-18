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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  read_show_stats () ; 
 scalar_t__ read_sockets ; 
 scalar_t__ server ; 
 int start_time ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_now (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_sockets_close_cb(uv_handle_t* handle) {
  free(handle);
  read_sockets--;

  /* If it's past the first second and everyone has closed their connection
   * Then print stats.
   */
  if (uv_now(loop) - start_time > 1000 && read_sockets == 0) {
    read_show_stats();
    uv_close((uv_handle_t*)server, NULL);
  }
}