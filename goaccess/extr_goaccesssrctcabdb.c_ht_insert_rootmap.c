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
 int /*<<< orphan*/  MTRC_ROOTMAP ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ins_is32 (void*,int,char const*) ; 

int
ht_insert_rootmap (GModule module, int key, const char *value)
{
  void *hash = get_hash (module, MTRC_ROOTMAP);

  if (!hash)
    return -1;

  return ins_is32 (hash, key, value);
}