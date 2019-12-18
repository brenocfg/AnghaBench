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
struct TYPE_4__ {int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  uid; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ user_t ;
struct lev_username {int user_id; char* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exact_strdup (char*,int) ; 
 int /*<<< orphan*/  exact_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,int) ; 
 TYPE_1__* get_user_f (int) ; 
 int /*<<< orphan*/  q_name ; 
 int /*<<< orphan*/  rehash_user_interests (TYPE_1__*) ; 
 int /*<<< orphan*/  save_words_hashlist_pattern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int set_username (struct lev_username *E, int len) {
  int i, j = 0;
  int user_id = E->user_id;
  char *text = E->s;

  assert (!text[len]);
  /*  if (user_id == 20205559 && verbosity > 0) {
    fprintf (stderr, "name of %d: '%s' (len=%d; now=%d, logpos=%lld)\n", user_id, text, len, now, log_cur_pos());
    }*/
  for (i = 0; i < len; i++) {
    if (text[i] == 9) { j++; }
    else if ((unsigned char) text[i] < ' ') { 
      fprintf (stderr, "name of %d: '%s' (len=%d)\n", user_id, text, len);
//      assert ((unsigned char) text[i] >= ' ');
      break;
    }
  }
  assert (j >= 0);
  user_t *U = get_user_f (user_id);
  if (U) {
    exact_strfree (U->name);
    U->name = exact_strdup (text, len);
    delete_user_hashlist (U->uid, U->name_hashes);
    U->name_hashes = save_words_hashlist_pattern (U->name, 0, ~2, 1, q_name);
    add_user_hashlist (U->uid, U->name_hashes);

    rehash_user_interests (U);
    return 1;
  }
  return 0;
}