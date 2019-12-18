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
struct TYPE_3__ {int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 unsigned int MAX_LANGS ; 
 int /*<<< orphan*/  add_user_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  field_value_hash (int /*<<< orphan*/ ,int) ; 
 int max_lang_id ; 
 int min_lang_id ; 
 int /*<<< orphan*/  q_lang_id ; 
 int /*<<< orphan*/  user_lang_pairs ; 

__attribute__((used)) static int add_user_lang (user_t *U, int lang_id) {
  if ((unsigned) lang_id >= MAX_LANGS) { 
    return -1;
  }
  if (lang_id > max_lang_id) {
    max_lang_id = lang_id;
  }
  if (lang_id < min_lang_id) {
    min_lang_id = lang_id;
  }

  user_lang_pairs++;

  add_user_word (U->uid, field_value_hash (q_lang_id, lang_id));

  return 1;
}