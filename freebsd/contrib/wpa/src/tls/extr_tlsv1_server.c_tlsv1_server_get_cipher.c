#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cipher_suite; } ;
struct tlsv1_server {TYPE_1__ rl; } ;

/* Variables and functions */
#define  TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA 148 
#define  TLS_DHE_RSA_WITH_AES_128_CBC_SHA 147 
#define  TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 146 
#define  TLS_DHE_RSA_WITH_AES_256_CBC_SHA 145 
#define  TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 144 
#define  TLS_DHE_RSA_WITH_DES_CBC_SHA 143 
#define  TLS_DH_anon_WITH_3DES_EDE_CBC_SHA 142 
#define  TLS_DH_anon_WITH_AES_128_CBC_SHA 141 
#define  TLS_DH_anon_WITH_AES_128_CBC_SHA256 140 
#define  TLS_DH_anon_WITH_AES_256_CBC_SHA 139 
#define  TLS_DH_anon_WITH_AES_256_CBC_SHA256 138 
#define  TLS_DH_anon_WITH_DES_CBC_SHA 137 
#define  TLS_DH_anon_WITH_RC4_128_MD5 136 
#define  TLS_RSA_WITH_3DES_EDE_CBC_SHA 135 
#define  TLS_RSA_WITH_AES_128_CBC_SHA 134 
#define  TLS_RSA_WITH_AES_128_CBC_SHA256 133 
#define  TLS_RSA_WITH_AES_256_CBC_SHA 132 
#define  TLS_RSA_WITH_AES_256_CBC_SHA256 131 
#define  TLS_RSA_WITH_DES_CBC_SHA 130 
#define  TLS_RSA_WITH_RC4_128_MD5 129 
#define  TLS_RSA_WITH_RC4_128_SHA 128 
 size_t os_strlcpy (char*,char*,size_t) ; 

int tlsv1_server_get_cipher(struct tlsv1_server *conn, char *buf,
			    size_t buflen)
{
	char *cipher;

	switch (conn->rl.cipher_suite) {
	case TLS_RSA_WITH_RC4_128_MD5:
		cipher = "RC4-MD5";
		break;
	case TLS_RSA_WITH_RC4_128_SHA:
		cipher = "RC4-SHA";
		break;
	case TLS_RSA_WITH_DES_CBC_SHA:
		cipher = "DES-CBC-SHA";
		break;
	case TLS_RSA_WITH_3DES_EDE_CBC_SHA:
		cipher = "DES-CBC3-SHA";
		break;
	case TLS_DHE_RSA_WITH_DES_CBC_SHA:
		cipher = "DHE-RSA-DES-CBC-SHA";
		break;
	case TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA:
		cipher = "DHE-RSA-DES-CBC3-SHA";
		break;
	case TLS_DH_anon_WITH_RC4_128_MD5:
		cipher = "ADH-RC4-MD5";
		break;
	case TLS_DH_anon_WITH_DES_CBC_SHA:
		cipher = "ADH-DES-SHA";
		break;
	case TLS_DH_anon_WITH_3DES_EDE_CBC_SHA:
		cipher = "ADH-DES-CBC3-SHA";
		break;
	case TLS_RSA_WITH_AES_128_CBC_SHA:
		cipher = "AES-128-SHA";
		break;
	case TLS_DHE_RSA_WITH_AES_128_CBC_SHA:
		cipher = "DHE-RSA-AES-128-SHA";
		break;
	case TLS_DH_anon_WITH_AES_128_CBC_SHA:
		cipher = "ADH-AES-128-SHA";
		break;
	case TLS_RSA_WITH_AES_256_CBC_SHA:
		cipher = "AES-256-SHA";
		break;
	case TLS_DHE_RSA_WITH_AES_256_CBC_SHA:
		cipher = "DHE-RSA-AES-256-SHA";
		break;
	case TLS_DH_anon_WITH_AES_256_CBC_SHA:
		cipher = "ADH-AES-256-SHA";
		break;
	case TLS_RSA_WITH_AES_128_CBC_SHA256:
		cipher = "AES-128-SHA256";
		break;
	case TLS_RSA_WITH_AES_256_CBC_SHA256:
		cipher = "AES-256-SHA256";
		break;
	case TLS_DHE_RSA_WITH_AES_128_CBC_SHA256:
		cipher = "DHE-RSA-AES-128-SHA256";
		break;
	case TLS_DHE_RSA_WITH_AES_256_CBC_SHA256:
		cipher = "DHE-RSA-AES-256-SHA256";
		break;
	case TLS_DH_anon_WITH_AES_128_CBC_SHA256:
		cipher = "ADH-AES-128-SHA256";
		break;
	case TLS_DH_anon_WITH_AES_256_CBC_SHA256:
		cipher = "ADH-AES-256-SHA256";
		break;
	default:
		return -1;
	}

	if (os_strlcpy(buf, cipher, buflen) >= buflen)
		return -1;
	return 0;
}