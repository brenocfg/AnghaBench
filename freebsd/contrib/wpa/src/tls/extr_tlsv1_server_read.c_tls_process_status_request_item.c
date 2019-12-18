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
struct tlsv1_server {int status_request_multi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void tls_process_status_request_item(struct tlsv1_server *conn,
					    const u8 *req, size_t req_len)
{
	const u8 *pos, *end;
	u8 status_type;

	pos = req;
	end = req + req_len;

	/*
	 * RFC 6961, 2.2:
	 * struct {
	 *   CertificateStatusType status_type;
	 *   uint16 request_length;
	 *   select (status_type) {
	 *     case ocsp: OCSPStatusRequest;
	 *     case ocsp_multi: OCSPStatusRequest;
	 *   } request;
	 * } CertificateStatusRequestItemV2;
	 *
	 * enum { ocsp(1), ocsp_multi(2), (255) } CertificateStatusType;
	 */

	if (end - pos < 1)
		return; /* Truncated data */

	status_type = *pos++;
	wpa_printf(MSG_DEBUG, "TLSv1: CertificateStatusType %u", status_type);
	if (status_type != 1 && status_type != 2)
		return; /* Unsupported status type */
	/*
	 * For now, only OCSP stapling is supported, so ignore the specific
	 * request, if any.
	 */
	wpa_hexdump(MSG_DEBUG, "TLSv1: OCSPStatusRequest", pos, end - pos);

	if (status_type == 2)
		conn->status_request_multi = 1;
}