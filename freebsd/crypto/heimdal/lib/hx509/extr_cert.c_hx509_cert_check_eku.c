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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ ExtKeyUsage ;

/* Variables and functions */
 int HX509_CERTIFICATE_MISSING_EKU ; 
 int /*<<< orphan*/  _hx509_get_cert (int /*<<< orphan*/ ) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int find_extension_eku (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  free_ExtKeyUsage (TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* id_any_eku ; 

int
hx509_cert_check_eku(hx509_context context, hx509_cert cert,
		     const heim_oid *eku, int allow_any_eku)
{
    ExtKeyUsage e;
    int ret;
    size_t i;

    ret = find_extension_eku(_hx509_get_cert(cert), &e);
    if (ret) {
	hx509_clear_error_string(context);
	return ret;
    }

    for (i = 0; i < e.len; i++) {
	if (der_heim_oid_cmp(eku, &e.val[i]) == 0) {
	    free_ExtKeyUsage(&e);
	    return 0;
	}
	if (allow_any_eku) {
#if 0
	    if (der_heim_oid_cmp(id_any_eku, &e.val[i]) == 0) {
		free_ExtKeyUsage(&e);
		return 0;
	    }
#endif
	}
    }
    free_ExtKeyUsage(&e);
    hx509_clear_error_string(context);
    return HX509_CERTIFICATE_MISSING_EKU;
}