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
struct lev_religion {int /*<<< orphan*/  str; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_RELIGION ; 
 int /*<<< orphan*/  add_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lev_religion* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_user_id (int) ; 
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exact_strdup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exact_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_simple_text (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_religion ; 
 int /*<<< orphan*/  save_words_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int do_set_religion (int user_id, const char *text, int len) {
  if (len < 0 || len >= 256 || conv_user_id (user_id) < 0) {
    return 0;
  }
  struct lev_religion *E = alloc_log_event (LEV_TARG_RELIGION + len, 9+len, user_id);

  filter_simple_text (E->str, text, len);

  user_t *U = get_user (E->user_id);

  if (U) {
    exact_strfree (U->religion);
    U->religion = exact_strdup (E->str, len);
    delete_user_hashlist (U->uid, U->religion_hashes);
    U->religion_hashes = save_words_hashlist (U->religion, 0, q_religion);
    add_user_hashlist (U->uid, U->religion_hashes);
    return 1;
  }

  return 0;
}