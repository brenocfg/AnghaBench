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
struct cache_uri {int size; } ;

/* Variables and functions */

__attribute__((used)) static int cache_uri_get_size_additional_storage_bytes (const struct cache_uri *U) {
  if (U->size & 0x80000000) {
    return 0;
  }
  return (U->size >> 24);
}