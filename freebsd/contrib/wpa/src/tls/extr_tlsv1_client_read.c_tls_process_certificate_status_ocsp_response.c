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
typedef  int u32 ;
struct tlsv1_client {int dummy; } ;
typedef  enum tls_ocsp_result { ____Placeholder_tls_ocsp_result } tls_ocsp_result ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int TLS_OCSP_INVALID ; 
 int WPA_GET_BE24 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tls_process_ocsp_response (struct tlsv1_client*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum tls_ocsp_result
tls_process_certificate_status_ocsp_response(struct tlsv1_client *conn,
					     const u8 *pos, size_t len)
{
	const u8 *end = pos + len;
	u32 ocsp_resp_len;

	/* opaque OCSPResponse<1..2^24-1>; */
	if (end - pos < 3) {
		wpa_printf(MSG_INFO, "TLSv1: Too short OCSPResponse");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return TLS_OCSP_INVALID;
	}
	ocsp_resp_len = WPA_GET_BE24(pos);
	pos += 3;
	if (end - pos < ocsp_resp_len) {
		wpa_printf(MSG_INFO, "TLSv1: Truncated OCSPResponse");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return TLS_OCSP_INVALID;
	}

	return tls_process_ocsp_response(conn, pos, ocsp_resp_len);
}