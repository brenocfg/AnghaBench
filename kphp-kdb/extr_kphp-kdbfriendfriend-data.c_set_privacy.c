#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pr_tree; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_8__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ privacy_t ;
typedef  int /*<<< orphan*/  privacy_key_t ;

/* Variables and functions */
 TYPE_2__* alloc_privacy () ; 
 int /*<<< orphan*/  privacy_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  privacy_replace (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_privacy_cats (TYPE_1__*) ; 

__attribute__((used)) static int set_privacy (user_t *U, privacy_key_t privacy_key, int force) {
  if (!U || !privacy_key) {
    return -1;
  }
  if (!force && !privacy_lookup (U->pr_tree, privacy_key)) {
    return -1;
  }

  save_privacy_cats (U);

  privacy_t *P = alloc_privacy();
  P->x = privacy_key;

  U->pr_tree = privacy_replace (U->pr_tree, P, 0);
  return 1;
}