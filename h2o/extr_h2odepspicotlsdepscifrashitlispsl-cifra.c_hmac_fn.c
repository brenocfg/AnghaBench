#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct TYPE_16__ {TYPE_1__ bytes; } ;
struct TYPE_17__ {TYPE_2__ u; } ;
typedef  TYPE_3__ sl_value ;
typedef  int /*<<< orphan*/  sl_symboltab ;
typedef  int /*<<< orphan*/  sl_iter ;
struct TYPE_18__ {int /*<<< orphan*/  hashsz; } ;
typedef  TYPE_4__ cf_chash ;

/* Variables and functions */
 int CF_MAXHASH ; 
 int /*<<< orphan*/  cf_hmac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__ const*) ; 
 int /*<<< orphan*/  sl_assert_bytes ; 
 int /*<<< orphan*/  sl_decref (TYPE_3__*) ; 
 TYPE_3__* sl_get_nil () ; 
 TYPE_3__* sl_iter_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_iter_start (TYPE_3__*) ; 
 TYPE_3__* sl_new_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_preprocess_eval ; 

__attribute__((used)) static sl_value * hmac_fn(sl_value *self, sl_value *args, sl_symboltab *tab, const cf_chash *h)
{
  sl_iter it = sl_iter_start(args);
  sl_value *key = sl_iter_convert(&it, sl_preprocess_eval, sl_assert_bytes, tab);
  sl_value *msg = sl_iter_convert(&it, sl_preprocess_eval, sl_assert_bytes, tab);

  if (!key || !msg)
  {
    sl_decref(key);
    sl_decref(msg);
    return sl_get_nil();
  }

  uint8_t result[CF_MAXHASH];
  cf_hmac(key->u.bytes.buf, key->u.bytes.len,
          msg->u.bytes.buf, msg->u.bytes.len,
          result,
          h);

  sl_decref(key);
  sl_decref(msg);
  return sl_new_bytes(result, h->hashsz);
}