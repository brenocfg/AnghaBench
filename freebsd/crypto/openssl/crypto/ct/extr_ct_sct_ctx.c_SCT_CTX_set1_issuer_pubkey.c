#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_PUBKEY ;
struct TYPE_3__ {int /*<<< orphan*/  ihashlen; int /*<<< orphan*/  ihash; } ;
typedef  TYPE_1__ SCT_CTX ;

/* Variables and functions */
 int ct_public_key_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int SCT_CTX_set1_issuer_pubkey(SCT_CTX *sctx, X509_PUBKEY *pubkey)
{
    return ct_public_key_hash(pubkey, &sctx->ihash, &sctx->ihashlen);
}