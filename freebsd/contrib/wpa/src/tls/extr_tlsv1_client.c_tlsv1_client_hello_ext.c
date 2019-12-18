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
struct tlsv1_client {int session_ticket_included; int client_hello_ext_len; int /*<<< orphan*/ * client_hello_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int TLS_EXT_PAC_OPAQUE ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int tlsv1_client_hello_ext(struct tlsv1_client *conn, int ext_type,
			   const u8 *data, size_t data_len)
{
	u8 *pos;

	conn->session_ticket_included = 0;
	os_free(conn->client_hello_ext);
	conn->client_hello_ext = NULL;
	conn->client_hello_ext_len = 0;

	if (data == NULL || data_len == 0)
		return 0;

	pos = conn->client_hello_ext = os_malloc(4 + data_len);
	if (pos == NULL)
		return -1;

	WPA_PUT_BE16(pos, ext_type);
	pos += 2;
	WPA_PUT_BE16(pos, data_len);
	pos += 2;
	os_memcpy(pos, data, data_len);
	conn->client_hello_ext_len = 4 + data_len;

	if (ext_type == TLS_EXT_PAC_OPAQUE) {
		conn->session_ticket_included = 1;
		wpa_printf(MSG_DEBUG, "TLSv1: Using session ticket");
	}

	return 0;
}