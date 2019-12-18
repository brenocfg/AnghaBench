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
typedef  int /*<<< orphan*/  serial_num ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  X509_NAME_oneline (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * X509_get_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openssl_pkey_type_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_snprintf_hex_uppercase (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void openssl_debug_dump_certificate(int i, X509 *cert)
{
	char buf[256];
	EVP_PKEY *pkey;
	ASN1_INTEGER *ser;
	char serial_num[128];

	X509_NAME_oneline(X509_get_subject_name(cert), buf, sizeof(buf));

	ser = X509_get_serialNumber(cert);
	if (ser)
		wpa_snprintf_hex_uppercase(serial_num, sizeof(serial_num),
					   ASN1_STRING_get0_data(ser),
					   ASN1_STRING_length(ser));
	else
		serial_num[0] = '\0';

	pkey = X509_get_pubkey(cert);
	wpa_printf(MSG_DEBUG, "%d: %s (%s) %s", i, buf,
		   openssl_pkey_type_str(pkey), serial_num);
	EVP_PKEY_free(pkey);
}