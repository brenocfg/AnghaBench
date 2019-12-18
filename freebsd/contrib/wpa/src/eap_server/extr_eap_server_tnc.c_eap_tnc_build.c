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
struct wpabuf {int dummy; } ;
struct eap_tnc_data {int /*<<< orphan*/  tncs; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_free (char*) ; 
 size_t os_strlen (char*) ; 
 int /*<<< orphan*/ * tncs_copy_send_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* tncs_if_tnccs_end () ; 
 char* tncs_if_tnccs_start (int /*<<< orphan*/ ) ; 
 size_t tncs_total_send_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_tnc_build(struct eap_sm *sm,
				     struct eap_tnc_data *data)
{
	struct wpabuf *req;
	u8 *rpos, *rpos1;
	size_t rlen;
	char *start_buf, *end_buf;
	size_t start_len, end_len;
	size_t imv_len;

	imv_len = tncs_total_send_len(data->tncs);

	start_buf = tncs_if_tnccs_start(data->tncs);
	if (start_buf == NULL)
		return NULL;
	start_len = os_strlen(start_buf);
	end_buf = tncs_if_tnccs_end();
	if (end_buf == NULL) {
		os_free(start_buf);
		return NULL;
	}
	end_len = os_strlen(end_buf);

	rlen = start_len + imv_len + end_len;
	req = wpabuf_alloc(rlen);
	if (req == NULL) {
		os_free(start_buf);
		os_free(end_buf);
		return NULL;
	}

	wpabuf_put_data(req, start_buf, start_len);
	os_free(start_buf);

	rpos1 = wpabuf_put(req, 0);
	rpos = tncs_copy_send_buf(data->tncs, rpos1);
	wpabuf_put(req, rpos - rpos1);

	wpabuf_put_data(req, end_buf, end_len);
	os_free(end_buf);

	wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-TNC: Request",
			  wpabuf_head(req), wpabuf_len(req));

	return req;
}