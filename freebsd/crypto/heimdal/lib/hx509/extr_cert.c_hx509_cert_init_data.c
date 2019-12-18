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
typedef  int /*<<< orphan*/  Certificate ;

/* Variables and functions */
 int HX509_EXTRA_DATA_AFTER_STRUCTURE ; 
 int decode_Certificate (void const*,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free_Certificate (int /*<<< orphan*/ *) ; 
 int hx509_cert_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
hx509_cert_init_data(hx509_context context,
		     const void *ptr,
		     size_t len,
		     hx509_cert *cert)
{
    Certificate t;
    size_t size;
    int ret;

    ret = decode_Certificate(ptr, len, &t, &size);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "Failed to decode certificate");
	return ret;
    }
    if (size != len) {
	free_Certificate(&t);
	hx509_set_error_string(context, 0, HX509_EXTRA_DATA_AFTER_STRUCTURE,
			       "Extra data after certificate");
	return HX509_EXTRA_DATA_AFTER_STRUCTURE;
    }

    ret = hx509_cert_init(context, &t, cert);
    free_Certificate(&t);
    return ret;
}