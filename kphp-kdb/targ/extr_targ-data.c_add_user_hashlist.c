#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; int /*<<< orphan*/ * A; } ;
typedef  TYPE_1__ hash_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_word (int,int /*<<< orphan*/ ) ; 

void add_user_hashlist (int uid, hash_list_t *H) {
  int i;
  if (!H || H->len <= 0) { return; }
  for (i = 0; i < H->len; i++) {
    add_user_word (uid, H->A[i]);
  }
}