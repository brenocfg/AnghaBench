#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* x; int /*<<< orphan*/ * y; } ;
typedef  TYPE_2__ shmap_pair_string_vptr ;
struct TYPE_13__ {scalar_t__ lock; char* name; TYPE_5__* q; TYPE_1__* prev_st; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_3__ qkey ;
struct TYPE_14__ {int /*<<< orphan*/  keys_cnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  ref_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEF ; 
 int /*<<< orphan*/  add_entry_time (TYPE_3__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  del_entry_time (TYPE_3__*) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  dl_log_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_strfree (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  h_qkey ; 
 int /*<<< orphan*/  qkey_free (TYPE_3__*) ; 
 int /*<<< orphan*/  queue_fix (TYPE_5__*) ; 
 int /*<<< orphan*/  shmap_string_vptr_del (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  str_memory ; 
 int verbosity ; 

void delete_qkey (qkey *k) {
  assert (k != NULL);

  del_entry_time (k);
  if (k->lock) {
    dl_log_add (LOG_DEF, 0, "trying to del locked key (%d)(key name = %s)(queue pointer = %p)(timeout = %d)!\n", k->lock, k->name, k->q, k->timeout);
    add_entry_time (k, 100);
    return;
  }
//  dl_log_add (LOG_DEF, 0, "trying to del key %p (%d)(key name = [%s]:%p)(queue pointer = %p)(timeout = %d)!\n", k, k->lock, k->name, k->name, k->q, k->timeout);

  assert (k->lock == 0);

  if (k->prev_st != NULL) {
    k->prev_st->ref_cnt--;
  }
  k->q->keys_cnt--;
  queue_fix (k->q);

  shmap_pair_string_vptr a;
  a.y = NULL;
  a.x = k->name;

  if (verbosity > 2) {
    fprintf (stderr, "Key deleted : [%s]\n", k->name);
  }
  dbg ("Key deleted : [%s]\n", k->name);
  shmap_string_vptr_del (&h_qkey, a);


  str_memory -= dl_get_memory_used();
  dl_strfree (k->name);
  str_memory += dl_get_memory_used();

  qkey_free (k);
}