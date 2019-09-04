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
 int /*<<< orphan*/  MTRC_MAXTS ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_iu64 (void*,int) ; 
 int /*<<< orphan*/  ins_iu64 (void*,int,int /*<<< orphan*/ ) ; 

int
ht_insert_maxts (GModule module, int key, uint64_t value)
{
  uint64_t curvalue = 0;
  void *hash = get_hash (module, MTRC_MAXTS);

  if (!hash)
    return -1;

  if ((curvalue = get_iu64 (hash, key)) < value)
    ins_iu64 (hash, key, value);

  return 0;
}