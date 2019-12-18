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
typedef  int /*<<< orphan*/  uid_t ;
struct kafs_token {int /*<<< orphan*/  ticket; int /*<<< orphan*/  ticket_len; int /*<<< orphan*/  ct; } ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int kafs_settoken_rxkad (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v5_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,struct kafs_token*) ; 

int
kafs_settoken5(krb5_context context, const char *cell, uid_t uid,
	       krb5_creds *cred)
{
    struct kafs_token kt;
    int ret;

    ret = v5_convert(context, NULL, cred, uid, cell, &kt);
    if (ret)
	return ret;

    ret = kafs_settoken_rxkad(cell, &kt.ct, kt.ticket, kt.ticket_len);

    free(kt.ticket);

    return ret;
}