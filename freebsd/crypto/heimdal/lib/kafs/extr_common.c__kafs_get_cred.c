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
struct kafs_token {int dummy; } ;
struct kafs_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_SUPERUSER ; 
 int /*<<< orphan*/  _kafs_foldup (char*,char const*) ; 
 scalar_t__ _kafs_realm_of_cell (struct kafs_data*,char const*,char**) ; 
 int _kafs_try_get_cred (struct kafs_data*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,struct kafs_token*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

int
_kafs_get_cred(struct kafs_data *data,
	       const char *cell,
	       const char *realm_hint,
	       const char *realm,
	       uid_t uid,
	       struct kafs_token *kt)
{
    int ret = -1;
    char *vl_realm;
    char CELL[64];

    /* We're about to find the realm that holds the key for afs in
     * the specified cell. The problem is that null-instance
     * afs-principals are common and that hitting the wrong realm might
     * yield the wrong afs key. The following assumptions were made.
     *
     * Any realm passed to us is preferred.
     *
     * If there is a realm with the same name as the cell, it is most
     * likely the correct realm to talk to.
     *
     * In most (maybe even all) cases the database servers of the cell
     * will live in the realm we are looking for.
     *
     * Try the local realm, but if the previous cases fail, this is
     * really a long shot.
     *
     */

    /* comments on the ordering of these tests */

    /* If the user passes a realm, she probably knows something we don't
     * know and we should try afs@realm_hint.
     */

    if (realm_hint) {
	ret = _kafs_try_get_cred(data, AUTH_SUPERUSER,
				 cell, realm_hint, uid, kt);
	if (ret == 0) return 0;
	ret = _kafs_try_get_cred(data, AUTH_SUPERUSER,
				 NULL, realm_hint, uid, kt);
	if (ret == 0) return 0;
    }

    _kafs_foldup(CELL, cell);

    /*
     * If the AFS servers have a file /usr/afs/etc/krb.conf containing
     * REALM we still don't have to resort to cross-cell authentication.
     * Try afs.cell@REALM.
     */
    ret = _kafs_try_get_cred(data, AUTH_SUPERUSER,
			     cell, realm, uid, kt);
    if (ret == 0) return 0;

    /*
     * If cell == realm we don't need no cross-cell authentication.
     * Try afs@REALM.
     */
    if (strcmp(CELL, realm) == 0) {
        ret = _kafs_try_get_cred(data, AUTH_SUPERUSER,
				 NULL, realm, uid, kt);
	if (ret == 0) return 0;
    }

    /*
     * We failed to get ``first class tickets'' for afs,
     * fall back to cross-cell authentication.
     * Try afs@CELL.
     * Try afs.cell@CELL.
     */
    ret = _kafs_try_get_cred(data, AUTH_SUPERUSER,
			     NULL, CELL, uid, kt);
    if (ret == 0) return 0;
    ret = _kafs_try_get_cred(data, AUTH_SUPERUSER,
			     cell, CELL, uid, kt);
    if (ret == 0) return 0;

    /*
     * Perhaps the cell doesn't correspond to any realm?
     * Use realm of first volume location DB server.
     * Try afs.cell@VL_REALM.
     * Try afs@VL_REALM???
     */
    if (_kafs_realm_of_cell(data, cell, &vl_realm) == 0
	&& strcmp(vl_realm, realm) != 0
	&& strcmp(vl_realm, CELL) != 0) {
	ret = _kafs_try_get_cred(data, AUTH_SUPERUSER,
				 cell, vl_realm, uid, kt);
	if (ret)
	    ret = _kafs_try_get_cred(data, AUTH_SUPERUSER,
				     NULL, vl_realm, uid, kt);
	free(vl_realm);
	if (ret == 0) return 0;
    }

    return ret;
}