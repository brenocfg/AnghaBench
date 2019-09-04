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
 int /*<<< orphan*/  MTRC_HITS ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ii32_min_max (void*,int*,int*) ; 

void
ht_get_hits_min_max (GModule module, int *min, int *max)
{
  void *hash = get_hash (module, MTRC_HITS);

  if (!hash)
    return;

  get_ii32_min_max (hash, min, max);
}