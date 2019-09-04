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
typedef  int /*<<< orphan*/  uv_connect_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  client_handle ; 
 int connect_cb_called ; 
 int /*<<< orphan*/  server_handle ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  /* |status| should equal 0 because the connection should have been accepted,
   * it's just that the server immediately closes it again.
   */
  ASSERT(0 == status);
  connect_cb_called += 1;
  uv_close((uv_handle_t*) &server_handle, NULL);
  uv_close((uv_handle_t*) &client_handle, NULL);
}