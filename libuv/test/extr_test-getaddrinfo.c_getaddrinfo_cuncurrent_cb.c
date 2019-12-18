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
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ uv_getaddrinfo_t ;
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CONCURRENT_COUNT ; 
 int /*<<< orphan*/ * callback_counts ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  getaddrinfo_cbs ; 
 TYPE_1__* getaddrinfo_handles ; 
 int /*<<< orphan*/  uv_freeaddrinfo (struct addrinfo*) ; 

__attribute__((used)) static void getaddrinfo_cuncurrent_cb(uv_getaddrinfo_t* handle,
                                      int status,
                                      struct addrinfo* res) {
  int i;
  int* data = (int*)handle->data;

  for (i = 0; i < CONCURRENT_COUNT; i++) {
    if (&getaddrinfo_handles[i] == handle) {
      ASSERT(i == *data);

      callback_counts[i]++;
      break;
    }
  }
  ASSERT (i < CONCURRENT_COUNT);

  free(data);
  uv_freeaddrinfo(res);

  getaddrinfo_cbs++;
}