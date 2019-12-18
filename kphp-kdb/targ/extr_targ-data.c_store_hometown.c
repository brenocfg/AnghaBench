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
struct TYPE_3__ {scalar_t__ hometown_hashes; scalar_t__ hometown; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_hashlist (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ exact_strdup (char*,int) ; 
 int /*<<< orphan*/  exact_strfree (scalar_t__) ; 
 int /*<<< orphan*/  q_hometown ; 
 scalar_t__ save_words_hashlist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int store_hometown (user_t *U, char *hometown, int len) {
  int i;
  assert (len <= 255);
  assert (!hometown[len]);
  for (i = 0; i < len; i++) {
    assert ((unsigned char) hometown[i] >= ' ');
  }
  exact_strfree (U->hometown);
  delete_user_hashlist (U->uid, U->hometown_hashes);

  if (len) {
    U->hometown = exact_strdup (hometown, len);
    U->hometown_hashes = save_words_hashlist (U->hometown, 0, q_hometown);
    add_user_hashlist (U->uid, U->hometown_hashes);
  } else {
    U->hometown = 0;
    U->hometown_hashes = 0;
  }

  return 1;
}