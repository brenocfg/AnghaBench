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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct tlsv1_server {size_t num_cipher_suites; int /*<<< orphan*/ * cipher_suites; } ;

/* Variables and functions */
 scalar_t__ TLS_CIPHER_ANON_DH_AES128_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_3DES_EDE_CBC_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_AES_128_CBC_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_AES_256_CBC_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_DES_CBC_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_RC4_128_MD5 ; 
 int /*<<< orphan*/  TLS_RSA_WITH_3DES_EDE_CBC_SHA ; 
 int /*<<< orphan*/  TLS_RSA_WITH_AES_128_CBC_SHA ; 
 int /*<<< orphan*/  TLS_RSA_WITH_AES_256_CBC_SHA ; 
 int /*<<< orphan*/  TLS_RSA_WITH_RC4_128_MD5 ; 
 int /*<<< orphan*/  TLS_RSA_WITH_RC4_128_SHA ; 

int tlsv1_server_set_cipher_list(struct tlsv1_server *conn, u8 *ciphers)
{
	size_t count;
	u16 *suites;

	/* TODO: implement proper configuration of cipher suites */
	if (ciphers[0] == TLS_CIPHER_ANON_DH_AES128_SHA) {
		count = 0;
		suites = conn->cipher_suites;
		suites[count++] = TLS_RSA_WITH_AES_256_CBC_SHA;
		suites[count++] = TLS_RSA_WITH_AES_128_CBC_SHA;
		suites[count++] = TLS_RSA_WITH_3DES_EDE_CBC_SHA;
		suites[count++] = TLS_RSA_WITH_RC4_128_SHA;
		suites[count++] = TLS_RSA_WITH_RC4_128_MD5;
		suites[count++] = TLS_DH_anon_WITH_AES_256_CBC_SHA;
		suites[count++] = TLS_DH_anon_WITH_AES_128_CBC_SHA;
		suites[count++] = TLS_DH_anon_WITH_3DES_EDE_CBC_SHA;
		suites[count++] = TLS_DH_anon_WITH_RC4_128_MD5;
		suites[count++] = TLS_DH_anon_WITH_DES_CBC_SHA;
		conn->num_cipher_suites = count;
	}

	return 0;
}