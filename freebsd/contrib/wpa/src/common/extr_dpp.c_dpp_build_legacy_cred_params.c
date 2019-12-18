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
struct wpabuf {int dummy; } ;
struct dpp_configuration {int /*<<< orphan*/  psk; scalar_t__ psk_set; scalar_t__ passphrase; } ;
typedef  int /*<<< orphan*/  psk ;
typedef  int /*<<< orphan*/  pass ;

/* Variables and functions */
 int /*<<< orphan*/  json_escape_string (char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  os_memset (char*,int /*<<< orphan*/ ,int) ; 
 int os_strlen (scalar_t__) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static void dpp_build_legacy_cred_params(struct wpabuf *buf,
					 struct dpp_configuration *conf)
{
	if (conf->passphrase && os_strlen(conf->passphrase) < 64) {
		char pass[63 * 6 + 1];

		json_escape_string(pass, sizeof(pass), conf->passphrase,
				   os_strlen(conf->passphrase));
		wpabuf_put_str(buf, "\"pass\":\"");
		wpabuf_put_str(buf, pass);
		wpabuf_put_str(buf, "\"");
		os_memset(pass, 0, sizeof(pass));
	} else if (conf->psk_set) {
		char psk[2 * sizeof(conf->psk) + 1];

		wpa_snprintf_hex(psk, sizeof(psk),
				 conf->psk, sizeof(conf->psk));
		wpabuf_put_str(buf, "\"psk_hex\":\"");
		wpabuf_put_str(buf, psk);
		wpabuf_put_str(buf, "\"");
		os_memset(psk, 0, sizeof(psk));
	}
}