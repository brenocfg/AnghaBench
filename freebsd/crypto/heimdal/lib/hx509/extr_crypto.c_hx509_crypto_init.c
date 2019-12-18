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
struct hx509cipher {int /*<<< orphan*/  (* evp_func ) () ;} ;
typedef  TYPE_1__* hx509_crypto ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_5__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  c; struct hx509cipher const* cipher; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HX509_ALG_NOT_SUPP ; 
 int /*<<< orphan*/  PADDING_PKCS7 ; 
 TYPE_1__* calloc (int,int) ; 
 scalar_t__ der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 struct hx509cipher* find_cipher_by_oid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_crypto_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stub1 () ; 

int
hx509_crypto_init(hx509_context context,
		  const char *provider,
		  const heim_oid *enctype,
		  hx509_crypto *crypto)
{
    const struct hx509cipher *cipher;

    *crypto = NULL;

    cipher = find_cipher_by_oid(enctype);
    if (cipher == NULL) {
	hx509_set_error_string(context, 0, HX509_ALG_NOT_SUPP,
			       "Algorithm not supported");
	return HX509_ALG_NOT_SUPP;
    }

    *crypto = calloc(1, sizeof(**crypto));
    if (*crypto == NULL) {
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    (*crypto)->flags = PADDING_PKCS7;
    (*crypto)->cipher = cipher;
    (*crypto)->c = (*cipher->evp_func)();

    if (der_copy_oid(enctype, &(*crypto)->oid)) {
	hx509_crypto_destroy(*crypto);
	*crypto = NULL;
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    return 0;
}