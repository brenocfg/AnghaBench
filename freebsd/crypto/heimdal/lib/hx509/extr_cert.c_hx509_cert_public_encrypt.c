#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_1__* hx509_cert ;
typedef  int /*<<< orphan*/  heim_oid ;
typedef  int /*<<< orphan*/  heim_octet_string ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int _hx509_public_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
hx509_cert_public_encrypt(hx509_context context,
			   const heim_octet_string *cleartext,
			   const hx509_cert p,
			   heim_oid *encryption_oid,
			   heim_octet_string *ciphertext)
{
    return _hx509_public_encrypt(context,
				 cleartext, p->data,
				 encryption_oid, ciphertext);
}