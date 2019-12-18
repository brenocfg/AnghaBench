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
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  contentType ;
typedef  int /*<<< orphan*/  PKCS12_Attributes ;

/* Variables and functions */
 int /*<<< orphan*/  _hx509_collector_get_lock (struct hx509_collector*) ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_data ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_1__*) ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_cms_decrypt_encrypted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int parse_safe_content (int /*<<< orphan*/ ,struct hx509_collector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
encryptedData_parser(hx509_context context,
		     struct hx509_collector *c,
		     const void *data, size_t length,
		     const PKCS12_Attributes *attrs)
{
    heim_octet_string content;
    heim_oid contentType;
    int ret;

    memset(&contentType, 0, sizeof(contentType));

    ret = hx509_cms_decrypt_encrypted(context,
				      _hx509_collector_get_lock(c),
				      data, length,
				      &contentType,
				      &content);
    if (ret)
	return ret;

    if (der_heim_oid_cmp(&contentType, &asn1_oid_id_pkcs7_data) == 0)
	ret = parse_safe_content(context, c, content.data, content.length);

    der_free_octet_string(&content);
    der_free_oid(&contentType);
    return ret;
}