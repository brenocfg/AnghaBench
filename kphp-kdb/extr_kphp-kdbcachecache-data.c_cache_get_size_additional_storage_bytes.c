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

/* Variables and functions */

__attribute__((used)) static int cache_get_size_additional_storage_bytes (long long size) {
  if (size < 0x7fffffff) {
    return 0;
  }
  if (size <= 0xffffffffLL) {
    return 1;
  }
  if (size <= 0xffffffffffLL) {
    return 2;
  }
  if (size <= 0xffffffffffffLL) {
    return 3;
  }
  if (size <= 0xffffffffffffffLL) {
    return 4;
  }
  return 5;
}