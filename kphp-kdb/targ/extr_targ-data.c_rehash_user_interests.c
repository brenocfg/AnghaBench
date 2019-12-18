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
struct TYPE_3__ {int /*<<< orphan*/  inter_hashes; int /*<<< orphan*/  uid; scalar_t__ name; struct interest* inter; } ;
typedef  TYPE_1__ user_t ;
struct interest {scalar_t__ text; struct interest* next; } ;

/* Variables and functions */
 scalar_t__ Hc ; 
 int /*<<< orphan*/  add_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_words_hashlist (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_interests ; 
 int /*<<< orphan*/  save_words_hashlist (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rehash_user_interests (user_t *U) {
  struct interest *I;
  if (!U) {
    return;
  }
  Hc = 0;
  for (I = U->inter; I; I = I->next) {
    prepare_words_hashlist (I->text, 1, -1, 0, q_interests);
  }
  if (U->name) {
    prepare_words_hashlist (U->name, 1, 2, 0, q_interests);
  }
  delete_user_hashlist (U->uid, U->inter_hashes);
  U->inter_hashes = save_words_hashlist (0, -1, q_interests);
  add_user_hashlist (U->uid, U->inter_hashes);
}