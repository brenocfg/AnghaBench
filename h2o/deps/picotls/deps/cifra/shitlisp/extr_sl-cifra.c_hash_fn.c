#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct TYPE_15__ {TYPE_1__ bytes; } ;
struct TYPE_16__ {TYPE_2__ u; } ;
typedef  TYPE_3__ sl_value ;
typedef  int /*<<< orphan*/  sl_symboltab ;
typedef  int /*<<< orphan*/  sl_iter ;
typedef  int /*<<< orphan*/  cf_chash_ctx ;
struct TYPE_17__ {scalar_t__ ctxsz; int hashsz; int /*<<< orphan*/  (* digest ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ cf_chash ;

/* Variables and functions */
 scalar_t__ CF_CHASH_MAXCTX ; 
 int CF_MAXHASH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sl_assert_bytes ; 
 int /*<<< orphan*/  sl_decref (TYPE_3__*) ; 
 TYPE_3__* sl_get_nil () ; 
 TYPE_3__* sl_iter_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_iter_start (TYPE_3__*) ; 
 TYPE_3__* sl_new_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sl_preprocess_eval ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sl_value * hash_fn(sl_value *self, sl_value *args, sl_symboltab *tab, const cf_chash *h)
{
  sl_iter it = sl_iter_start(args);
  sl_value *msg = sl_iter_convert(&it, sl_preprocess_eval, sl_assert_bytes, tab);

  if (!msg)
    return sl_get_nil();

  cf_chash_ctx ctx;
  assert(h->ctxsz <= CF_CHASH_MAXCTX);
  h->init(&ctx);
  h->update(&ctx, msg->u.bytes.buf, msg->u.bytes.len);
  sl_decref(msg);

  uint8_t result[CF_MAXHASH];
  assert(h->hashsz <= CF_MAXHASH);
  h->digest(&ctx, result);

  return sl_new_bytes(result, h->hashsz);
}