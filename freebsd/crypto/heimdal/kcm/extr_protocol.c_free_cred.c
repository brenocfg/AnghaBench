#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kcm_ntlm_cred {int /*<<< orphan*/  nthash; struct kcm_ntlm_cred* domain; struct kcm_ntlm_cred* user; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct kcm_ntlm_cred*) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_cred(struct kcm_ntlm_cred *cred)
{
    free(cred->user);
    free(cred->domain);
    krb5_data_free(&cred->nthash);
    free(cred);
}