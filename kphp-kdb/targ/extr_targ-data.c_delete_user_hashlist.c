#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_t ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * A; } ;
typedef  TYPE_1__ hash_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  delete_user_word (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_free (TYPE_1__*,int,int) ; 

void delete_user_hashlist (int uid, hash_list_t *H) {
  int i;
  if (!H || H->len <= 0) { return; }
  for (i = 0; i < H->len; i++) {
    delete_user_word (uid, H->A[i]);
  }
  dyn_free (H, 8 + H->len * sizeof(hash_t), 8);
}