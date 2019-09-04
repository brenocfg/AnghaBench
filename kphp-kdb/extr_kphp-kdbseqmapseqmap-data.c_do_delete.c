#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lev_seq_delete {int /*<<< orphan*/  data; } ;
struct item {int key_len; } ;

/* Variables and functions */
 scalar_t__ LEV_SEQ_DELETE ; 
 struct lev_seq_delete* alloc_log_event (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int delete_lev (struct lev_seq_delete*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 struct item* preload_key (int,int const*,int) ; 

int do_delete (int key_len, const int *key, int force) {
  struct item *I = preload_key (key_len, key, force);
  if (I->key_len == -2) {
    return -2;
  }
  assert (key_len >= 0 && key_len <= 255);
  struct lev_seq_delete *E = alloc_log_event (LEV_SEQ_DELETE + key_len, sizeof (*E) + key_len * 4, 0);
  memcpy (E->data, key, 4 * key_len);
  return delete_lev (E);
}