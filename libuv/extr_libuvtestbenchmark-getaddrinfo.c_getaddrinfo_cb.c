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
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ TOTAL_CALLS ; 
 int /*<<< orphan*/  calls_completed ; 
 scalar_t__ calls_initiated ; 
 int /*<<< orphan*/  getaddrinfo_initiate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_freeaddrinfo (struct addrinfo*) ; 

__attribute__((used)) static void getaddrinfo_cb(uv_getaddrinfo_t* handle, int status,
    struct addrinfo* res) {
  ASSERT(status == 0);
  calls_completed++;
  if (calls_initiated < TOTAL_CALLS) {
    getaddrinfo_initiate(handle);
  }

  uv_freeaddrinfo(res);
}