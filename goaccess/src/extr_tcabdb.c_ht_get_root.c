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
 int /*<<< orphan*/  MTRC_ROOT ; 
 int /*<<< orphan*/  MTRC_ROOTMAP ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_ii32 (void*,int) ; 
 char* get_is32 (void*,int) ; 

char *
ht_get_root (GModule module, int key)
{
  int root_key = 0;
  void *hashroot = get_hash (module, MTRC_ROOT);
  void *hashrootmap = get_hash (module, MTRC_ROOTMAP);

  if (!hashroot || !hashrootmap)
    return NULL;

  /* not found */
  if ((root_key = get_ii32 (hashroot, key)) == 0)
    return NULL;

  return get_is32 (hashrootmap, root_key);
}