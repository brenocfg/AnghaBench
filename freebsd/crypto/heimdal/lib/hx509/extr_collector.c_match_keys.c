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
struct private_key {int /*<<< orphan*/ * private_key; } ;
typedef  int /*<<< orphan*/  hx509_cursor ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;

/* Variables and functions */
 int HX509_CERT_NOT_FOUND ; 
 int HX509_PRIVATE_KEY_MISSING ; 
 int /*<<< orphan*/  _hx509_cert_assign_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _hx509_cert_private_key (int /*<<< orphan*/ *) ; 
 int _hx509_match_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_end_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hx509_certs_next_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int hx509_certs_start_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
match_keys(hx509_context context, struct private_key *value, hx509_certs certs)
{
    hx509_cursor cursor;
    hx509_cert c;
    int ret, found = HX509_CERT_NOT_FOUND;

    if (value->private_key == NULL) {
	hx509_set_error_string(context, 0, HX509_PRIVATE_KEY_MISSING,
			       "No private key to compare with");
	return HX509_PRIVATE_KEY_MISSING;
    }

    ret = hx509_certs_start_seq(context, certs, &cursor);
    if (ret)
	return ret;

    c = NULL;
    while (1) {
	ret = hx509_certs_next_cert(context, certs, cursor, &c);
	if (ret)
	    break;
	if (c == NULL)
	    break;
	if (_hx509_cert_private_key(c)) {
	    hx509_cert_free(c);
	    continue;
	}

	ret = _hx509_match_keys(c, value->private_key);
	if (ret) {
	    _hx509_cert_assign_key(c, value->private_key);
	    hx509_cert_free(c);
	    found = 0;
	    break;
	}
	hx509_cert_free(c);
    }

    hx509_certs_end_seq(context, certs, cursor);

    if (found)
	hx509_clear_error_string(context);

    return found;
}