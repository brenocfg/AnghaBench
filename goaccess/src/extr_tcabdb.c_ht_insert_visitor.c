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
 int /*<<< orphan*/  MTRC_VISITORS ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inc_ii32 (void*,int,int) ; 

int
ht_insert_visitor (GModule module, int key, int inc)
{
  void *hash = get_hash (module, MTRC_VISITORS);

  if (!hash)
    return -1;

  return inc_ii32 (hash, key, inc);
}