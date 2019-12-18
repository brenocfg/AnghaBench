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
struct tls_dn_field_order_cnt {int dummy; } ;
typedef  int /*<<< orphan*/  field ;
typedef  int /*<<< orphan*/  dn_cnt ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 char* cstr_token (char const*,char*,char const**) ; 
 int /*<<< orphan*/  get_value_from_field (int /*<<< orphan*/ *,char*,struct tls_dn_field_order_cnt*) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  os_memset (struct tls_dn_field_order_cnt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int tls_match_dn_field(X509 *cert, const char *match)
{
	const char *token, *last = NULL;
	char field[256];
	struct tls_dn_field_order_cnt dn_cnt;

	os_memset(&dn_cnt, 0, sizeof(dn_cnt));

	/* Maximum length of each DN field is 255 characters */

	/* Process each '/' delimited field */
	while ((token = cstr_token(match, "/", &last))) {
		if (last - token >= (int) sizeof(field)) {
			wpa_printf(MSG_ERROR,
				   "OpenSSL: Too long DN matching field value in '%s'",
				   match);
			return 0;
		}
		os_memcpy(field, token, last - token);
		field[last - token] = '\0';

		if (!get_value_from_field(cert, field, &dn_cnt)) {
			wpa_printf(MSG_DEBUG, "OpenSSL: No match for DN '%s'",
				   field);
			return 0;
		}
	}

	return 1;
}