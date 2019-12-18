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
struct krb5_kafs_data {int /*<<< orphan*/  context; int /*<<< orphan*/  realm; int /*<<< orphan*/  id; } ;
struct kafs_token {int /*<<< orphan*/ * ticket; int /*<<< orphan*/  ticket_len; int /*<<< orphan*/  ct; } ;
struct kafs_data {struct krb5_kafs_data* data; } ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 scalar_t__ _kafs_afslog_all_local_cells (struct kafs_data*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ _kafs_get_cred (struct kafs_data*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct kafs_token*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ kafs_settoken_rxkad (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
afslog_uid_int(struct kafs_data *data, const char *cell, const char *rh,
	       uid_t uid, const char *homedir)
{
    krb5_error_code ret;
    struct kafs_token kt;
    krb5_principal princ;
    const char *trealm; /* ticket realm */
    struct krb5_kafs_data *d = data->data;

    if (cell == 0 || cell[0] == 0)
	return _kafs_afslog_all_local_cells (data, uid, homedir);

    ret = krb5_cc_get_principal (d->context, d->id, &princ);
    if (ret)
	return ret;

    trealm = krb5_principal_get_realm (d->context, princ);

    kt.ticket = NULL;
    ret = _kafs_get_cred(data, cell, d->realm, trealm, uid, &kt);
    krb5_free_principal (d->context, princ);

    if(ret == 0) {
	ret = kafs_settoken_rxkad(cell, &kt.ct, kt.ticket, kt.ticket_len);
	free(kt.ticket);
    }
    return ret;
}