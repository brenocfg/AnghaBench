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
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_defns; int /*<<< orphan*/  load_pubkey; int /*<<< orphan*/  load_privkey; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  finish; int /*<<< orphan*/  init; int /*<<< orphan*/  destroy; int /*<<< orphan*/  pkey_meths; int /*<<< orphan*/  digests; int /*<<< orphan*/  ciphers; int /*<<< orphan*/  rand_meth; int /*<<< orphan*/  ec_meth; int /*<<< orphan*/  dh_meth; int /*<<< orphan*/  dsa_meth; int /*<<< orphan*/  rsa_meth; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */

__attribute__((used)) static void engine_cpy(ENGINE *dest, const ENGINE *src)
{
    dest->id = src->id;
    dest->name = src->name;
#ifndef OPENSSL_NO_RSA
    dest->rsa_meth = src->rsa_meth;
#endif
#ifndef OPENSSL_NO_DSA
    dest->dsa_meth = src->dsa_meth;
#endif
#ifndef OPENSSL_NO_DH
    dest->dh_meth = src->dh_meth;
#endif
#ifndef OPENSSL_NO_EC
    dest->ec_meth = src->ec_meth;
#endif
    dest->rand_meth = src->rand_meth;
    dest->ciphers = src->ciphers;
    dest->digests = src->digests;
    dest->pkey_meths = src->pkey_meths;
    dest->destroy = src->destroy;
    dest->init = src->init;
    dest->finish = src->finish;
    dest->ctrl = src->ctrl;
    dest->load_privkey = src->load_privkey;
    dest->load_pubkey = src->load_pubkey;
    dest->cmd_defns = src->cmd_defns;
    dest->flags = src->flags;
}