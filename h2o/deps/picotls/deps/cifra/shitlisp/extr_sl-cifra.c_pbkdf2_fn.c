#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * v; } ;
struct TYPE_16__ {TYPE_14__ bn; } ;
struct TYPE_17__ {TYPE_1__ integer; } ;
struct TYPE_18__ {TYPE_2__ u; } ;
typedef  TYPE_3__ sl_value ;
typedef  int /*<<< orphan*/  sl_symboltab ;
typedef  int /*<<< orphan*/  sl_iter ;
typedef  int /*<<< orphan*/  cf_chash ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int bignum_len_words (TYPE_14__*) ; 
 TYPE_3__* do_pbkdf2 (int /*<<< orphan*/  const*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_assert_bytes ; 
 int /*<<< orphan*/  sl_assert_integer ; 
 int /*<<< orphan*/  sl_decref (TYPE_3__*) ; 
 TYPE_3__* sl_get_nil () ; 
 TYPE_3__* sl_iter_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_iter_start (TYPE_3__*) ; 
 int /*<<< orphan*/  sl_preprocess_eval ; 

__attribute__((used)) static sl_value * pbkdf2_fn(sl_value *self, sl_value *args, sl_symboltab *tab, const cf_chash *h)
{
  sl_iter it = sl_iter_start(args);
  sl_value *pw = sl_iter_convert(&it, sl_preprocess_eval, sl_assert_bytes, tab);
  sl_value *salt = sl_iter_convert(&it, sl_preprocess_eval, sl_assert_bytes, tab);
  sl_value *iterations = sl_iter_convert(&it, sl_preprocess_eval, sl_assert_integer, tab);
  sl_value *outlen = sl_iter_convert(&it, sl_preprocess_eval, sl_assert_integer, tab);

  sl_value *ret;

  if (!pw || !salt || !iterations || !outlen)
    ret = sl_get_nil();
  else
  {
    assert(bignum_len_words(&iterations->u.integer.bn) == 1);
    assert(bignum_len_words(&outlen->u.integer.bn) == 1);
    ret = do_pbkdf2(h, pw, salt,
                    iterations->u.integer.bn.v[0],
                    outlen->u.integer.bn.v[0]);
  }
  
  sl_decref(pw);
  sl_decref(salt);
  sl_decref(iterations);
  sl_decref(outlen);
  return ret;
}