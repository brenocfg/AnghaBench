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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  ExtKeyUsage ;

/* Variables and functions */
 int HX509_EXTENSION_NOT_FOUND ; 
 int /*<<< orphan*/  _hx509_get_cert (int /*<<< orphan*/ ) ; 
 int find_extension_eku (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
_hx509_cert_get_eku(hx509_context context,
		    hx509_cert cert,
		    ExtKeyUsage *e)
{
    int ret;

    memset(e, 0, sizeof(*e));

    ret = find_extension_eku(_hx509_get_cert(cert), e);
    if (ret && ret != HX509_EXTENSION_NOT_FOUND) {
	hx509_clear_error_string(context);
	return ret;
    }
    return 0;
}