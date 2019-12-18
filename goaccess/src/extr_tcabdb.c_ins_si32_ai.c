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
 int ht_get_size (void*) ; 
 int ins_si32 (void*,char const*,int) ; 

__attribute__((used)) static int
ins_si32_ai (void *hash, const char *key)
{
  int size = 0, value = 0;

  if (!hash)
    return -1;

  size = ht_get_size (hash);
  /* the auto increment value starts at SIZE (hash table) + 1 */
  value = size > 0 ? size + 1 : 1;

  if (ins_si32 (hash, key, value) == -1)
    return -1;

  return value;
}