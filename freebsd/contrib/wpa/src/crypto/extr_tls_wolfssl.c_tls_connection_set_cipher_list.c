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
typedef  int u8 ;
struct tls_connection {int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  TLS_CIPHER_AES128_SHA 133 
#define  TLS_CIPHER_AES256_SHA 132 
#define  TLS_CIPHER_ANON_DH_AES128_SHA 131 
 int TLS_CIPHER_NONE ; 
#define  TLS_CIPHER_RC4_SHA 130 
#define  TLS_CIPHER_RSA_DHE_AES128_SHA 129 
#define  TLS_CIPHER_RSA_DHE_AES256_SHA 128 
 int os_snprintf (char*,int,char*,char const*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int wolfSSL_set_cipher_list (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tls_connection_set_cipher_list(void *tls_ctx, struct tls_connection *conn,
				   u8 *ciphers)
{
	char buf[128], *pos, *end;
	u8 *c;
	int ret;

	if (!conn || !conn->ssl || !ciphers)
		return -1;

	buf[0] = '\0';
	pos = buf;
	end = pos + sizeof(buf);

	c = ciphers;
	while (*c != TLS_CIPHER_NONE) {
		const char *suite;

		switch (*c) {
		case TLS_CIPHER_RC4_SHA:
			suite = "RC4-SHA";
			break;
		case TLS_CIPHER_AES128_SHA:
			suite = "AES128-SHA";
			break;
		case TLS_CIPHER_RSA_DHE_AES128_SHA:
			suite = "DHE-RSA-AES128-SHA";
			break;
		case TLS_CIPHER_ANON_DH_AES128_SHA:
			suite = "ADH-AES128-SHA";
			break;
		case TLS_CIPHER_RSA_DHE_AES256_SHA:
			suite = "DHE-RSA-AES256-SHA";
			break;
		case TLS_CIPHER_AES256_SHA:
			suite = "AES256-SHA";
			break;
		default:
			wpa_printf(MSG_DEBUG,
				   "TLS: Unsupported cipher selection: %d", *c);
			return -1;
		}
		ret = os_snprintf(pos, end - pos, ":%s", suite);
		if (os_snprintf_error(end - pos, ret))
			break;
		pos += ret;

		c++;
	}

	wpa_printf(MSG_DEBUG, "wolfSSL: cipher suites: %s", buf + 1);

	if (wolfSSL_set_cipher_list(conn->ssl, buf + 1) != 1) {
		wpa_printf(MSG_DEBUG, "Cipher suite configuration failed");
		return -1;
	}

	return 0;
}