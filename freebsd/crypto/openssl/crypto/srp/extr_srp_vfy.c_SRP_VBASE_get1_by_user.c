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
struct TYPE_4__ {char* seed_key; int /*<<< orphan*/ * default_N; int /*<<< orphan*/ * default_g; } ;
typedef  int /*<<< orphan*/  SRP_user_pwd ;
typedef  TYPE_1__ SRP_VBASE ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 scalar_t__ RAND_priv_bytes (unsigned char*,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SRP_user_pwd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SRP_user_pwd_new () ; 
 int /*<<< orphan*/  SRP_user_pwd_set_gN (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRP_user_pwd_set_ids (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ SRP_user_pwd_set_sv_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_user (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * srp_user_pwd_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

SRP_user_pwd *SRP_VBASE_get1_by_user(SRP_VBASE *vb, char *username)
{
    SRP_user_pwd *user;
    unsigned char digv[SHA_DIGEST_LENGTH];
    unsigned char digs[SHA_DIGEST_LENGTH];
    EVP_MD_CTX *ctxt = NULL;

    if (vb == NULL)
        return NULL;

    if ((user = find_user(vb, username)) != NULL)
        return srp_user_pwd_dup(user);

    if ((vb->seed_key == NULL) ||
        (vb->default_g == NULL) || (vb->default_N == NULL))
        return NULL;

/* if the user is unknown we set parameters as well if we have a seed_key */

    if ((user = SRP_user_pwd_new()) == NULL)
        return NULL;

    SRP_user_pwd_set_gN(user, vb->default_g, vb->default_N);

    if (!SRP_user_pwd_set_ids(user, username, NULL))
        goto err;

    if (RAND_priv_bytes(digv, SHA_DIGEST_LENGTH) <= 0)
        goto err;
    ctxt = EVP_MD_CTX_new();
    if (ctxt == NULL
        || !EVP_DigestInit_ex(ctxt, EVP_sha1(), NULL)
        || !EVP_DigestUpdate(ctxt, vb->seed_key, strlen(vb->seed_key))
        || !EVP_DigestUpdate(ctxt, username, strlen(username))
        || !EVP_DigestFinal_ex(ctxt, digs, NULL))
        goto err;
    EVP_MD_CTX_free(ctxt);
    ctxt = NULL;
    if (SRP_user_pwd_set_sv_BN(user,
                               BN_bin2bn(digs, SHA_DIGEST_LENGTH, NULL),
                               BN_bin2bn(digv, SHA_DIGEST_LENGTH, NULL)))
        return user;

 err:
    EVP_MD_CTX_free(ctxt);
    SRP_user_pwd_free(user);
    return NULL;
}