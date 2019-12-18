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
ht_improve_hash_(unsigned h)
{
  /* Aim to protect against poor hash functions by adding logic here
   * - logic taken from java 1.4 hashtable source */
  h += ~(h << 9);
  h ^=  ((h >> 14) | (h << 18)); /* >>> */
  h +=  (h << 4);
  h ^=  ((h >> 10) | (h << 22)); /* >>> */
  return h;
}