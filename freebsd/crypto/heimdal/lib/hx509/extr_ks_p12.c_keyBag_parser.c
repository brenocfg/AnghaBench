#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hx509_collector {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_octet_string ;
struct TYPE_7__ {int /*<<< orphan*/  attrValues; } ;
struct TYPE_6__ {int /*<<< orphan*/  privateKey; int /*<<< orphan*/  privateKeyAlgorithm; } ;
typedef  TYPE_1__ PKCS8PrivateKeyInfo ;
typedef  int /*<<< orphan*/  PKCS12_Attributes ;
typedef  TYPE_2__ PKCS12_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  _hx509_collector_private_key_add (int /*<<< orphan*/ ,struct hx509_collector*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs_9_at_localKeyId ; 
 int decode_PKCS8PrivateKeyInfo (void const*,size_t,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* find_attribute (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_PKCS8PrivateKeyInfo (TYPE_1__*) ; 

__attribute__((used)) static int
keyBag_parser(hx509_context context,
	      struct hx509_collector *c,
	      const void *data, size_t length,
	      const PKCS12_Attributes *attrs)
{
    const PKCS12_Attribute *attr;
    PKCS8PrivateKeyInfo ki;
    const heim_octet_string *os = NULL;
    int ret;

    attr = find_attribute(attrs, &asn1_oid_id_pkcs_9_at_localKeyId);
    if (attr)
	os = &attr->attrValues;

    ret = decode_PKCS8PrivateKeyInfo(data, length, &ki, NULL);
    if (ret)
	return ret;

    _hx509_collector_private_key_add(context,
				     c,
				     &ki.privateKeyAlgorithm,
				     NULL,
				     &ki.privateKey,
				     os);
    free_PKCS8PrivateKeyInfo(&ki);
    return 0;
}