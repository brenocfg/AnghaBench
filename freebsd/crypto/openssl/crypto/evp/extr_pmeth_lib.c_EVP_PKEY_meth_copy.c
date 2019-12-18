#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  check; int /*<<< orphan*/  ctrl_str; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  derive; int /*<<< orphan*/  derive_init; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  decrypt_init; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  encrypt_init; int /*<<< orphan*/  verifyctx; int /*<<< orphan*/  verifyctx_init; int /*<<< orphan*/  signctx; int /*<<< orphan*/  signctx_init; int /*<<< orphan*/  verify_recover; int /*<<< orphan*/  verify_recover_init; int /*<<< orphan*/  verify; int /*<<< orphan*/  verify_init; int /*<<< orphan*/  sign; int /*<<< orphan*/  sign_init; int /*<<< orphan*/  keygen; int /*<<< orphan*/  keygen_init; int /*<<< orphan*/  paramgen; int /*<<< orphan*/  paramgen_init; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  copy; int /*<<< orphan*/  init; } ;
typedef  TYPE_1__ EVP_PKEY_METHOD ;

/* Variables and functions */

void EVP_PKEY_meth_copy(EVP_PKEY_METHOD *dst, const EVP_PKEY_METHOD *src)
{

    dst->init = src->init;
    dst->copy = src->copy;
    dst->cleanup = src->cleanup;

    dst->paramgen_init = src->paramgen_init;
    dst->paramgen = src->paramgen;

    dst->keygen_init = src->keygen_init;
    dst->keygen = src->keygen;

    dst->sign_init = src->sign_init;
    dst->sign = src->sign;

    dst->verify_init = src->verify_init;
    dst->verify = src->verify;

    dst->verify_recover_init = src->verify_recover_init;
    dst->verify_recover = src->verify_recover;

    dst->signctx_init = src->signctx_init;
    dst->signctx = src->signctx;

    dst->verifyctx_init = src->verifyctx_init;
    dst->verifyctx = src->verifyctx;

    dst->encrypt_init = src->encrypt_init;
    dst->encrypt = src->encrypt;

    dst->decrypt_init = src->decrypt_init;
    dst->decrypt = src->decrypt;

    dst->derive_init = src->derive_init;
    dst->derive = src->derive;

    dst->ctrl = src->ctrl;
    dst->ctrl_str = src->ctrl_str;

    dst->check = src->check;
}