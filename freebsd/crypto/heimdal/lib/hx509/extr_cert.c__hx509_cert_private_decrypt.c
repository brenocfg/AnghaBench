#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_1__* hx509_cert ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_9__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ heim_octet_string ;
struct TYPE_8__ {int /*<<< orphan*/ * private_key; } ;

/* Variables and functions */
 int HX509_PRIVATE_KEY_MISSING ; 
 int hx509_private_key_private_decrypt (int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
_hx509_cert_private_decrypt(hx509_context context,
			    const heim_octet_string *ciphertext,
			    const heim_oid *encryption_oid,
			    hx509_cert p,
			    heim_octet_string *cleartext)
{
    cleartext->data = NULL;
    cleartext->length = 0;

    if (p->private_key == NULL) {
	hx509_set_error_string(context, 0, HX509_PRIVATE_KEY_MISSING,
			       "Private key missing");
	return HX509_PRIVATE_KEY_MISSING;
    }

    return hx509_private_key_private_decrypt(context,
					      ciphertext,
					      encryption_oid,
					      p->private_key,
					      cleartext);
}