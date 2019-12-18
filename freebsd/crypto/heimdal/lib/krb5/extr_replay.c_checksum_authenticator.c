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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int len; int /*<<< orphan*/ ** val; } ;
struct TYPE_6__ {TYPE_1__ name_string; } ;
struct TYPE_7__ {int /*<<< orphan*/  cusec; int /*<<< orphan*/  ctime; TYPE_2__ cname; int /*<<< orphan*/ * crealm; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_3__ Authenticator ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
checksum_authenticator(Authenticator *auth, void *data)
{
    EVP_MD_CTX *m = EVP_MD_CTX_create();
    unsigned i;

    EVP_DigestInit_ex(m, EVP_md5(), NULL);

    EVP_DigestUpdate(m, auth->crealm, strlen(auth->crealm));
    for(i = 0; i < auth->cname.name_string.len; i++)
	EVP_DigestUpdate(m, auth->cname.name_string.val[i],
		   strlen(auth->cname.name_string.val[i]));
    EVP_DigestUpdate(m, &auth->ctime, sizeof(auth->ctime));
    EVP_DigestUpdate(m, &auth->cusec, sizeof(auth->cusec));

    EVP_DigestFinal_ex(m, data, NULL);
    EVP_MD_CTX_destroy(m);
}