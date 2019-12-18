#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  inactive_ads; int /*<<< orphan*/  active_ads; } ;
typedef  TYPE_1__ user_t ;
typedef  scalar_t__ treeref_t ;
struct TYPE_5__ {scalar_t__ z; } ;

/* Variables and functions */
 int /*<<< orphan*/  AdSpace ; 
 TYPE_3__* TNODE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  active_ad_nodes ; 
 int /*<<< orphan*/  free_intree_node (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  inactive_ad_nodes ; 
 int /*<<< orphan*/  intree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  intree_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static inline void deactivate_one_user_ad (user_t *U, int ad_id) {
  treeref_t RN;
  U->active_ads = intree_remove (AdSpace, U->active_ads, ad_id, &RN);
  if (RN) {
    --active_ad_nodes;
    if (TNODE (AdSpace, RN)->z) {
      ++inactive_ad_nodes;
      U->inactive_ads = intree_insert (AdSpace, U->inactive_ads, RN);
    } else {
      free_intree_node (AdSpace, RN);
    }
  }
}