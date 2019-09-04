#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_4__ {scalar_t__ handle; } ;
typedef  TYPE_1__ uv_connect_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc_cb ; 
 int /*<<< orphan*/  connect_cb_called ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  read_cb ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  int r;

  ASSERT(req != NULL);
  ASSERT(status == 0);

  /* Not that the server will send anything, but otherwise we'll never know
   * when the server closes the connection. */
  r = uv_read_start((uv_stream_t*)(req->handle), alloc_cb, read_cb);
  ASSERT(r == 0);

  connect_cb_called++;

  free(req);
}