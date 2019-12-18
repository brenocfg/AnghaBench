#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_private_key ;
typedef  int hx509_key_format_t ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_8__ {unsigned char* data; int length; } ;
typedef  TYPE_3__ heim_octet_string ;
struct TYPE_6__ {int /*<<< orphan*/  rsa; } ;
struct TYPE_7__ {TYPE_1__ private_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int HX509_CRYPTO_KEY_FORMAT_UNSUPPORTED ; 
#define  HX509_KEY_FORMAT_DER 128 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int i2d_RSAPrivateKey (int /*<<< orphan*/ ,unsigned char**) ; 
 unsigned char* malloc (int) ; 

__attribute__((used)) static int
rsa_private_key_export(hx509_context context,
		       const hx509_private_key key,
		       hx509_key_format_t format,
		       heim_octet_string *data)
{
    int ret;

    data->data = NULL;
    data->length = 0;

    switch (format) {
    case HX509_KEY_FORMAT_DER:

	ret = i2d_RSAPrivateKey(key->private_key.rsa, NULL);
	if (ret <= 0) {
	    ret = EINVAL;
	    hx509_set_error_string(context, 0, ret,
			       "Private key is not exportable");
	    return ret;
	}

	data->data = malloc(ret);
	if (data->data == NULL) {
	    ret = ENOMEM;
	    hx509_set_error_string(context, 0, ret, "malloc out of memory");
	    return ret;
	}
	data->length = ret;

	{
	    unsigned char *p = data->data;
	    i2d_RSAPrivateKey(key->private_key.rsa, &p);
	}
	break;
    default:
	return HX509_CRYPTO_KEY_FORMAT_UNSUPPORTED;
    }

    return 0;
}