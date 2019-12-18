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
typedef  int /*<<< orphan*/  uv_getaddrinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  calls_initiated ; 
 int /*<<< orphan*/  getaddrinfo_cb ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  name ; 
 int uv_getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void getaddrinfo_initiate(uv_getaddrinfo_t* handle) {
  int r;

  calls_initiated++;

  r = uv_getaddrinfo(loop, handle, &getaddrinfo_cb, name, NULL, NULL);
  ASSERT(r == 0);
}