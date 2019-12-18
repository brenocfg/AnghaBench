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
struct hx509_collector {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  PKCS12_Attributes ;

/* Variables and functions */
 int decode_PKCS12_OctetString (void const*,size_t,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_1__*) ; 
 int parse_safe_content (int /*<<< orphan*/ ,struct hx509_collector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
safeContent_parser(hx509_context context,
		   struct hx509_collector *c,
		   const void *data, size_t length,
		   const PKCS12_Attributes *attrs)
{
    heim_octet_string os;
    int ret;

    ret = decode_PKCS12_OctetString(data, length, &os, NULL);
    if (ret)
	return ret;
    ret = parse_safe_content(context, c, os.data, os.length);
    der_free_octet_string(&os);
    return ret;
}