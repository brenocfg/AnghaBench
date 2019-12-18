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
 char* BUILT_WITH_DEFHASH ; 
 char* BUILT_WITH_TCBTREE ; 
 char* BUILT_WITH_TCMEMHASH ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

void
display_storage (void)
{
#ifdef TCB_BTREE
  fprintf (stdout, "%s\n", BUILT_WITH_TCBTREE);
#elif TCB_MEMHASH
  fprintf (stdout, "%s\n", BUILT_WITH_TCMEMHASH);
#else
  fprintf (stdout, "%s\n", BUILT_WITH_DEFHASH);
#endif
}