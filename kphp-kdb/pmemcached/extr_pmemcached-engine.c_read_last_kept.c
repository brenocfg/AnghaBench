#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct keep_mc_store {int dummy; } ;
struct connection {TYPE_1__* Tmp; } ;
typedef  int /*<<< orphan*/  nb_iterator_t ;
struct TYPE_7__ {scalar_t__ magic; scalar_t__ key_len; int /*<<< orphan*/  key; } ;
struct TYPE_6__ {int /*<<< orphan*/  total_bytes; } ;

/* Variables and functions */
 scalar_t__ MC_STORE_MAGIC ; 
 int advance_skip_read_ptr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* mc_store ; 
 int nbit_read_in (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ read_in (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

int read_last_kept (struct connection *c, int force) {
  if (c->Tmp) {
    nb_iterator_t R;
    nbit_set (&R, c->Tmp);
    int l = nbit_read_in (&R, mc_store, sizeof (struct keep_mc_store));
    if (l > 0 && (force || mc_store->magic == MC_STORE_MAGIC)) {
      assert (l == sizeof (struct keep_mc_store));
      assert (mc_store->magic == MC_STORE_MAGIC);
      assert (advance_skip_read_ptr (c->Tmp, sizeof (struct keep_mc_store)) == sizeof (struct keep_mc_store));
      assert (read_in (c->Tmp, mc_store->key, mc_store->key_len) == mc_store->key_len);
      assert (!c->Tmp->total_bytes);
      //assert ((nbit_read_in (&R, mc_store->key, mc_store->key_len)) == mc_store->key_len);
      return 1;
    }
    return 0;
  }
  return 0;
}