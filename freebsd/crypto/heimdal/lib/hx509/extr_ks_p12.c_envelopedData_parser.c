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
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  contentType ;
typedef  int /*<<< orphan*/  PKCS12_Attributes ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_ERROR_APPEND ; 
 int /*<<< orphan*/  _hx509_collector_get_lock (struct hx509_collector*) ; 
 int /*<<< orphan*/  _hx509_lock_unlock_certs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_data ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_1__*) ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_cms_unenvelope (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int parse_safe_content (int /*<<< orphan*/ ,struct hx509_collector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
envelopedData_parser(hx509_context context,
		     struct hx509_collector *c,
		     const void *data, size_t length,
		     const PKCS12_Attributes *attrs)
{
    heim_octet_string content;
    heim_oid contentType;
    hx509_lock lock;
    int ret;

    memset(&contentType, 0, sizeof(contentType));

    lock = _hx509_collector_get_lock(c);

    ret = hx509_cms_unenvelope(context,
			       _hx509_lock_unlock_certs(lock),
			       0,
			       data, length,
			       NULL,
			       0,
			       &contentType,
			       &content);
    if (ret) {
	hx509_set_error_string(context, HX509_ERROR_APPEND, ret,
			       "PKCS12 failed to unenvelope");
	return ret;
    }

    if (der_heim_oid_cmp(&contentType, &asn1_oid_id_pkcs7_data) == 0)
	ret = parse_safe_content(context, c, content.data, content.length);

    der_free_octet_string(&content);
    der_free_oid(&contentType);

    return ret;
}