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
struct store_ctx {int format; int /*<<< orphan*/  f; } ;
typedef  int /*<<< orphan*/  hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ heim_octet_string ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_KEY_FORMAT_DER ; 
#define  USE_DER 129 
#define  USE_PEM 128 
 int /*<<< orphan*/  _hx509_cert_private_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hx509_cert_private_key_exportable (int /*<<< orphan*/ ) ; 
 int _hx509_private_key_export (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* _hx509_private_pem_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int hx509_cert_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_pem_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
store_func(hx509_context context, void *ctx, hx509_cert c)
{
    struct store_ctx *sc = ctx;
    heim_octet_string data;
    int ret;

    ret = hx509_cert_binary(context, c, &data);
    if (ret)
	return ret;

    switch (sc->format) {
    case USE_DER:
	fwrite(data.data, data.length, 1, sc->f);
	free(data.data);
	break;
    case USE_PEM:
	hx509_pem_write(context, "CERTIFICATE", NULL, sc->f,
			data.data, data.length);
	free(data.data);
	if (_hx509_cert_private_key_exportable(c)) {
	    hx509_private_key key = _hx509_cert_private_key(c);
	    ret = _hx509_private_key_export(context, key,
					    HX509_KEY_FORMAT_DER, &data);
	    if (ret)
		break;
	    hx509_pem_write(context, _hx509_private_pem_name(key), NULL, sc->f,
			    data.data, data.length);
	    free(data.data);
	}
	break;
    }

    return 0;
}