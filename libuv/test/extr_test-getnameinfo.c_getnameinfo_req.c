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
typedef  int /*<<< orphan*/  uv_getnameinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static void getnameinfo_req(uv_getnameinfo_t* handle,
                            int status,
                            const char* hostname,
                            const char* service) {
  ASSERT(handle != NULL);
  ASSERT(status == 0);
  ASSERT(hostname != NULL);
  ASSERT(service != NULL);
}