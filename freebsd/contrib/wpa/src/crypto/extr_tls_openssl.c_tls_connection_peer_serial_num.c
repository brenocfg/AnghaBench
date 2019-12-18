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
struct tls_connection {int /*<<< orphan*/  peer_cert; } ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_serialNumber (int /*<<< orphan*/ ) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  wpa_snprintf_hex_uppercase (char*,size_t,int /*<<< orphan*/ ,int) ; 

char * tls_connection_peer_serial_num(void *tls_ctx,
				      struct tls_connection *conn)
{
	ASN1_INTEGER *ser;
	char *serial_num;
	size_t len;

	if (!conn->peer_cert)
		return NULL;

	ser = X509_get_serialNumber(conn->peer_cert);
	if (!ser)
		return NULL;

	len = ASN1_STRING_length(ser) * 2 + 1;
	serial_num = os_malloc(len);
	if (!serial_num)
		return NULL;
	wpa_snprintf_hex_uppercase(serial_num, len,
				   ASN1_STRING_get0_data(ser),
				   ASN1_STRING_length(ser));
	return serial_num;
}