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
typedef  int /*<<< orphan*/  ProcessList ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  CheckItem ;
typedef  int /*<<< orphan*/  Affinity ;

/* Variables and functions */
 int /*<<< orphan*/  Affinity_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * Affinity_new (int /*<<< orphan*/ *) ; 
 scalar_t__ CheckItem_get (int /*<<< orphan*/ *) ; 
 scalar_t__ Panel_get (int /*<<< orphan*/ *,int) ; 
 int Panel_size (int /*<<< orphan*/ *) ; 

Affinity* AffinityPanel_getAffinity(Panel* this, ProcessList* pl) {
   Affinity* affinity = Affinity_new(pl);
   int size = Panel_size(this);
   for (int i = 0; i < size; i++) {
      if (CheckItem_get((CheckItem*)Panel_get(this, i)))
         Affinity_add(affinity, i);
   }
   return affinity;
}