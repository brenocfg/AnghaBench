#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct TYPE_12__ {TYPE_2__ bytes; } ;
struct TYPE_14__ {TYPE_1__ u; } ;
typedef  TYPE_3__ sl_value ;
struct TYPE_15__ {scalar_t__ start; } ;
typedef  TYPE_4__ dstr ;
typedef  int /*<<< orphan*/  cf_chash ;

/* Variables and functions */
 int /*<<< orphan*/  cf_pbkdf2_hmac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ dstr_expand (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (TYPE_4__*) ; 
 int /*<<< orphan*/  dstr_init (TYPE_4__*) ; 
 TYPE_3__* sl_new_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sl_value * do_pbkdf2(const cf_chash *h, sl_value *pw, sl_value *salt,
                            uint32_t iterations, uint32_t outlen)
{
  dstr out;
  dstr_init(&out);
  if (dstr_expand(&out, outlen))
    return NULL;

  cf_pbkdf2_hmac(pw->u.bytes.buf, pw->u.bytes.len,
                 salt->u.bytes.buf, salt->u.bytes.len,
                 iterations,
                 (uint8_t *) out.start, outlen,
                 h);

  sl_value *ret = sl_new_bytes((uint8_t *) out.start, outlen);
  dstr_free(&out);
  return ret;
}