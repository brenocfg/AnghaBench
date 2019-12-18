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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_BW ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_iu64_min_max (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ht_get_bw_min_max (GModule module, uint64_t * min, uint64_t * max)
{
  void *hash = get_hash (module, MTRC_BW);

  if (!hash)
    return;

  get_iu64_min_max (hash, min, max);
}