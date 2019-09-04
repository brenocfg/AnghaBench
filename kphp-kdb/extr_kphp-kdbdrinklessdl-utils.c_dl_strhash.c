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
 unsigned long long HASH_MUL ; 

long long dl_strhash (const char *s) {
  unsigned long long h = 0;

  while (*s) {
    h = h * HASH_MUL + (unsigned long long)*s++;
  }

  return (long long)h;
}