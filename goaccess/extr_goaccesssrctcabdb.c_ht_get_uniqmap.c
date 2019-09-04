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
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_UNIQMAP ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_si32 (void*,char const*) ; 

int
ht_get_uniqmap (GModule module, const char *key)
{
  void *hash = get_hash (module, MTRC_UNIQMAP);

  if (!hash)
    return -1;

  return get_si32 (hash, key);
}