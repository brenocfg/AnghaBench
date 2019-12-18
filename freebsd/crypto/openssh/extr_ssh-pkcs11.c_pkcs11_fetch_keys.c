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
struct sshkey {int dummy; } ;
struct pkcs11_provider {int dummy; } ;
typedef  int /*<<< orphan*/  pubkey_class ;
typedef  int /*<<< orphan*/  cert_class ;
struct TYPE_4__ {int member_2; int /*<<< orphan*/ * pValue; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  CK_ULONG ;
typedef  int /*<<< orphan*/  CK_OBJECT_CLASS ;
typedef  TYPE_1__ CK_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  CKA_CLASS ; 
 int /*<<< orphan*/  CKA_ID ; 
 int /*<<< orphan*/  CKA_MODULUS ; 
 int /*<<< orphan*/  CKA_PUBLIC_EXPONENT ; 
 int /*<<< orphan*/  CKA_SUBJECT ; 
 int /*<<< orphan*/  CKA_VALUE ; 
 int /*<<< orphan*/  CKO_CERTIFICATE ; 
 int /*<<< orphan*/  CKO_PUBLIC_KEY ; 
 scalar_t__ pkcs11_fetch_keys_filter (struct pkcs11_provider*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,struct sshkey***,int*) ; 

__attribute__((used)) static int
pkcs11_fetch_keys(struct pkcs11_provider *p, CK_ULONG slotidx,
    struct sshkey ***keysp, int *nkeys)
{
	CK_OBJECT_CLASS	pubkey_class = CKO_PUBLIC_KEY;
	CK_OBJECT_CLASS	cert_class = CKO_CERTIFICATE;
	CK_ATTRIBUTE		pubkey_filter[] = {
		{ CKA_CLASS, NULL, sizeof(pubkey_class) }
	};
	CK_ATTRIBUTE		cert_filter[] = {
		{ CKA_CLASS, NULL, sizeof(cert_class) }
	};
	CK_ATTRIBUTE		pubkey_attribs[] = {
		{ CKA_ID, NULL, 0 },
		{ CKA_MODULUS, NULL, 0 },
		{ CKA_PUBLIC_EXPONENT, NULL, 0 }
	};
	CK_ATTRIBUTE		cert_attribs[] = {
		{ CKA_ID, NULL, 0 },
		{ CKA_SUBJECT, NULL, 0 },
		{ CKA_VALUE, NULL, 0 }
	};
	pubkey_filter[0].pValue = &pubkey_class;
	cert_filter[0].pValue = &cert_class;

	if (pkcs11_fetch_keys_filter(p, slotidx, pubkey_filter, pubkey_attribs,
	    keysp, nkeys) < 0 ||
	    pkcs11_fetch_keys_filter(p, slotidx, cert_filter, cert_attribs,
	    keysp, nkeys) < 0)
		return (-1);
	return (0);
}