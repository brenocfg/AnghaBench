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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  KeyUsage ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KeyUsage2int (int /*<<< orphan*/ ) ; 
 int _hx509_cert_get_keyusage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asn1_KeyUsage_units () ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  unparse_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
hx509_cert_keyusage_print(hx509_context context, hx509_cert c, char **s)
{
    KeyUsage ku;
    char buf[256];
    int ret;

    *s = NULL;

    ret = _hx509_cert_get_keyusage(context, c, &ku);
    if (ret)
	return ret;
    unparse_flags(KeyUsage2int(ku), asn1_KeyUsage_units(), buf, sizeof(buf));
    *s = strdup(buf);
    if (*s == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    return 0;
}