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
struct tlsv1_server {int status_request_v2; } ;

/* Variables and functions */
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tls_process_status_request_item (struct tlsv1_server*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void tls_process_status_request_v2(struct tlsv1_server *conn,
					  const u8 *ext, size_t ext_len)
{
	const u8 *pos, *end;

	conn->status_request_v2 = 1;

	pos = ext;
	end = ext + ext_len;

	/*
	 * RFC 6961, 2.2:
	 * struct {
	 *   CertificateStatusRequestItemV2
	 *                    certificate_status_req_list<1..2^16-1>;
	 * } CertificateStatusRequestListV2;
	 */

	while (end - pos >= 2) {
		u16 len;

		len = WPA_GET_BE16(pos);
		pos += 2;
		if (len > end - pos)
			break; /* Truncated data */
		tls_process_status_request_item(conn, pos, len);
		pos += len;
	}
}