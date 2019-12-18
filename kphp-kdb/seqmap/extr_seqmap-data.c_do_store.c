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
struct lev_seq_store_time {int time; int value_len; scalar_t__ data; } ;
struct lev_seq_store_inf {int value_len; scalar_t__ data; } ;
struct item {int key_len; } ;

/* Variables and functions */
 scalar_t__ LEV_SEQ_STORE_INF ; 
 scalar_t__ LEV_SEQ_STORE_TIME ; 
 void* alloc_log_event (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int const*,int) ; 
 int now ; 
 struct item* preload_key (int,int const*,int) ; 
 int store_inf (struct lev_seq_store_inf*) ; 
 int store_time (struct lev_seq_store_time*) ; 

int do_store (int mode, int key_len, const int *key, int value_len, const int *value, int delay, int force) {
  if (delay <= now && delay > 0) {
    return 0;
  }
  struct item *I = preload_key (key_len, key, force && (mode != 3));
  if (I->key_len == -2) {
    return -2;
  }
  
  assert (key_len <= 255);
  if (delay <= 0) {
    struct lev_seq_store_inf *E = alloc_log_event (LEV_SEQ_STORE_INF + mode * 256 + key_len, sizeof (*E) + key_len * 4 + value_len * 4, 0);
    E->value_len = value_len;
    memcpy (E->data, key, 4 * key_len);
    memcpy (E->data + key_len, value, 4 * value_len);
    return store_inf (E);
  } else {
    struct lev_seq_store_time *E = alloc_log_event (LEV_SEQ_STORE_TIME + mode * 256 + key_len, sizeof (*E) + key_len * 4 + value_len * 4, 0);
    E->time = delay;
    E->value_len = value_len;
    memcpy (E->data, key, 4 * key_len);
    memcpy (E->data + key_len, value, 4 * value_len);
    return store_time (E);
  }
}