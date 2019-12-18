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
typedef  int /*<<< orphan*/  ht_t ;

/* Variables and functions */
 intptr_t strcmp (void const*,void const*) ; 

intptr_t on_strcmp(ht_t ht, const void *key1, const void *key2) {
  if (key1 == key2 || !key1 || !key2) {
    return (key1 == key2 ? 0 : key1 ? -1 : 1);
  }
  return strcmp(key1, key2);
}