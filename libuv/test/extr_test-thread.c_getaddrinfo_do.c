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
struct getaddrinfo_req {int /*<<< orphan*/  handle; int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  getaddrinfo_cb ; 
 int uv_getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void getaddrinfo_do(struct getaddrinfo_req* req) {
  int r;

  r = uv_getaddrinfo(req->loop,
                     &req->handle,
                     getaddrinfo_cb,
                     "localhost",
                     NULL,
                     NULL);
  ASSERT(r == 0);
}