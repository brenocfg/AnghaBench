#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sign_id; int hash_id; int pkey_id; } ;
typedef  TYPE_1__ nid_triple ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OBJ_F_OBJ_ADD_SIGID ; 
 int /*<<< orphan*/  OBJerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/ * sig_app ; 
 int /*<<< orphan*/  sig_sk_cmp ; 
 int /*<<< orphan*/ * sigx_app ; 
 int /*<<< orphan*/  sigx_cmp ; 
 int /*<<< orphan*/ * sk_nid_triple_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_nid_triple_push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sk_nid_triple_sort (int /*<<< orphan*/ *) ; 

int OBJ_add_sigid(int signid, int dig_id, int pkey_id)
{
    nid_triple *ntr;
    if (sig_app == NULL)
        sig_app = sk_nid_triple_new(sig_sk_cmp);
    if (sig_app == NULL)
        return 0;
    if (sigx_app == NULL)
        sigx_app = sk_nid_triple_new(sigx_cmp);
    if (sigx_app == NULL)
        return 0;
    if ((ntr = OPENSSL_malloc(sizeof(*ntr))) == NULL) {
        OBJerr(OBJ_F_OBJ_ADD_SIGID, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    ntr->sign_id = signid;
    ntr->hash_id = dig_id;
    ntr->pkey_id = pkey_id;

    if (!sk_nid_triple_push(sig_app, ntr)) {
        OPENSSL_free(ntr);
        return 0;
    }

    if (!sk_nid_triple_push(sigx_app, ntr))
        return 0;

    sk_nid_triple_sort(sig_app);
    sk_nid_triple_sort(sigx_app);

    return 1;
}