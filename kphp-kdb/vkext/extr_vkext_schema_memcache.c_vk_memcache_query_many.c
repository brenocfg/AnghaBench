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
typedef  int /*<<< orphan*/  zval ;
struct rpc_query {int /*<<< orphan*/  qid; } ;
struct rpc_connection {int dummy; } ;
typedef  int /*<<< orphan*/  HashPosition ;

/* Variables and functions */
 scalar_t__ HASH_KEY_IS_STRING ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  Z_ARRVAL_PP (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  add_assoc_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_index_bool (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_index_long (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 struct rpc_query* vk_memcache_query_one (struct rpc_connection*,double,int /*<<< orphan*/ **) ; 
 scalar_t__ zend_hash_get_current_data_ex (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_hash_get_current_key_ex (int /*<<< orphan*/ ,char**,unsigned int*,unsigned long*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_internal_pointer_reset_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_move_forward_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vk_memcache_query_many (struct rpc_connection *c, zval **arr, double timeout, zval **r) {
  HashPosition pos;
  zend_hash_internal_pointer_reset_ex (Z_ARRVAL_PP (arr), &pos);
  zval **zkey;
  //int num = zend_hash_num_elements (Z_ARRVAL_PP (arr));
  //i nt cc = 0;
  array_init (*r);
  while (zend_hash_get_current_data_ex (Z_ARRVAL_PP (arr), (void **)&zkey, &pos) == SUCCESS) {
    char *key;
    unsigned int key_len;
    unsigned long index;
    if (zend_hash_get_current_key_ex (Z_ARRVAL_PP (arr), &key, &key_len, &index, 1, &pos) == HASH_KEY_IS_STRING) {
      index = 0;      
    } else {
      key = 0;
    }
    struct rpc_query *q = vk_memcache_query_one (c, timeout, zkey);
    zend_hash_move_forward_ex (Z_ARRVAL_PP(arr), &pos);
    if (key) {
      if (q) {
        add_assoc_long (*r, key, q->qid);
      } else {
        add_assoc_bool (*r, key, 0);
      }
    } else {
      if (q) {
        add_index_long (*r, index, q->qid);
      } else {
        add_index_bool (*r, index, 0);
      }
    }
  }
  //long long x = do_rpc_queue_create (cc, qids);
  //free (qids);
  //return r;
}