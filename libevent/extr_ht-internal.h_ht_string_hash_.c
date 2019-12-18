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

__attribute__((used)) static inline unsigned
ht_string_hash_(const char *s)
{
  unsigned h;
  const unsigned char *cp = (const unsigned char *)s;
  h = *cp << 7;
  while (*cp) {
    h = (1000003*h) ^ *cp++;
  }
  /* This conversion truncates the length of the string, but that's ok. */
  h ^= (unsigned)(cp-(const unsigned char*)s);
  return h;
}