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
struct TYPE_3__ {scalar_t__ proposal_hashes; scalar_t__ proposal; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_hashlist (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ exact_strdup (char*,int) ; 
 int /*<<< orphan*/  exact_strfree (scalar_t__) ; 
 int /*<<< orphan*/  prepare_words_hashlist (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_proposal ; 
 scalar_t__ save_words_hashlist (scalar_t__,int,int /*<<< orphan*/ ) ; 

int store_proposal (user_t *U, char *proposal, int len) {
  int i;
  assert (len <= 1023);
  assert ((!len && !proposal) || !proposal[len]);
  for (i = 0; i < len; i++) {
    assert ((unsigned char) proposal[i] >= ' ');
  }
  exact_strfree (U->proposal);
  delete_user_hashlist (U->uid, U->proposal_hashes);

  if (len) {
    U->proposal = exact_strdup (proposal, len);
    prepare_words_hashlist ("anyproposal", 0, -1, 0, q_proposal);
    U->proposal_hashes = save_words_hashlist (U->proposal, -1, q_proposal);
    add_user_hashlist (U->uid, U->proposal_hashes);
  } else {
    U->proposal = 0;
    U->proposal_hashes = 0;
  }

  return 1;
}