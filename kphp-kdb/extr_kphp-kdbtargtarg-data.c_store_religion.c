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
struct TYPE_3__ {int /*<<< orphan*/  religion_hashes; int /*<<< orphan*/  uid; int /*<<< orphan*/  religion; } ;
typedef  TYPE_1__ user_t ;
struct lev_religion {char* str; int type; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exact_stralloc (int) ; 
 int /*<<< orphan*/  exact_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_simple_text (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_religion ; 
 int /*<<< orphan*/  save_words_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int store_religion (struct lev_religion *E, int sz) {
  char *ptr = E->str;
  int len = E->type & 0xff;
  user_t *U;

  if (sz < len+9) { return -2; }

  assert (!ptr[len]);
//  fprintf (stderr, "%d: '%s'\n", E->user_id, E->str);

  U = get_user (E->user_id);

  if (U) {
    exact_strfree (U->religion);
    U->religion = exact_stralloc (len);
    filter_simple_text (U->religion, ptr, len);
    delete_user_hashlist (U->uid, U->religion_hashes);
    U->religion_hashes = save_words_hashlist (U->religion, 0, q_religion);
    add_user_hashlist (U->uid, U->religion_hashes);
  }

  return 9+len;
}