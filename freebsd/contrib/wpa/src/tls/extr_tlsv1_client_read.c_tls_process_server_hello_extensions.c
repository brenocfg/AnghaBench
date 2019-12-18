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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct tlsv1_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_process_server_hello_extensions(struct tlsv1_client *conn,
					       const u8 *pos, size_t len)
{
	const u8 *end = pos + len;

	wpa_hexdump(MSG_MSGDUMP, "TLSv1: ServerHello extensions",
		    pos, len);
	while (pos < end) {
		u16 ext, elen;

		if (end - pos < 4) {
			wpa_printf(MSG_INFO, "TLSv1: Truncated ServerHello extension header");
			return -1;
		}

		ext = WPA_GET_BE16(pos);
		pos += 2;
		elen = WPA_GET_BE16(pos);
		pos += 2;

		if (elen > end - pos) {
			wpa_printf(MSG_INFO, "TLSv1: Truncated ServerHello extension");
			return -1;
		}

		wpa_printf(MSG_DEBUG, "TLSv1: ServerHello ExtensionType %u",
			   ext);
		wpa_hexdump(MSG_DEBUG, "TLSv1: ServerHello extension data",
			    pos, elen);

		pos += elen;
	}

	return 0;
}