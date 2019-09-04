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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_connect_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc_cb ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  connect_cb_called ; 
 int /*<<< orphan*/  read_cb ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  int r;

  ASSERT(status == 0);
  connect_cb_called++;

  r = uv_read_start((uv_stream_t*)&conn, alloc_cb, read_cb);
  ASSERT(r == 0);
}