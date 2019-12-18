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
struct item {int key_len; } ;

/* Variables and functions */
 int NODE_TYPE_MINUS ; 
 int NODE_TYPE_UNSURE ; 
 int /*<<< orphan*/  alloc_item (int,int*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delete_time (struct item*) ; 
 int /*<<< orphan*/  delete_value (struct item*) ; 
 struct item* preload_key (int,int*,int /*<<< orphan*/ ) ; 

int delete (int E_size, void *E, int key_len, int *key) {
  assert (key_len >= 0 && key_len <= 255);
  struct item *I = preload_key (key_len, key, 0);
  delete_time (I);
  int t = I->key_len;
  if (I->key_len >= 0) {
    delete_value (I);
  } else {
    if (I->key_len == -3) {
      alloc_item (key_len, key, NODE_TYPE_MINUS | NODE_TYPE_UNSURE, -1);
    }
  }
  return t != -1;
}