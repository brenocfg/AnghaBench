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
typedef  int /*<<< orphan*/ * hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  _hx509_certs_keys_free (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int _hx509_certs_keys_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/ * _hx509_private_key_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*,...) ; 

__attribute__((used)) static int
read_private_key(const char *fn, hx509_private_key *key)
{
    hx509_private_key *keys;
    hx509_certs certs;
    int ret;

    *key = NULL;

    ret = hx509_certs_init(context, fn, 0, NULL, &certs);
    if (ret)
	hx509_err(context, 1, ret, "hx509_certs_init: %s", fn);

    ret = _hx509_certs_keys_get(context, certs, &keys);
    hx509_certs_free(&certs);
    if (ret)
	hx509_err(context, 1, ret, "hx509_certs_keys_get");
    if (keys[0] == NULL)
	errx(1, "no keys in key store: %s", fn);

    *key = _hx509_private_key_ref(keys[0]);
    _hx509_certs_keys_free(context, keys);

    return 0;
}