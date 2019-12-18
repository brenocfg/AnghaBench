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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
 unsigned char* base64_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 char const* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 char* soap_prefix ; 
 char* urn_wfawlanconfig ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char const*,...) ; 
 char* wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static struct wpabuf * wps_er_soap_hdr(const struct wpabuf *msg,
				       const char *name, const char *arg_name,
				       const char *path,
				       const struct sockaddr_in *dst,
				       char **len_ptr, char **body_ptr)
{
	unsigned char *encoded;
	size_t encoded_len;
	struct wpabuf *buf;

	if (msg) {
		encoded = base64_encode(wpabuf_head(msg), wpabuf_len(msg),
					&encoded_len);
		if (encoded == NULL)
			return NULL;
	} else {
		encoded = NULL;
		encoded_len = 0;
	}

	buf = wpabuf_alloc(1000 + encoded_len);
	if (buf == NULL) {
		os_free(encoded);
		return NULL;
	}

	wpabuf_printf(buf,
		      "POST %s HTTP/1.1\r\n"
		      "Host: %s:%d\r\n"
		      "Content-Type: text/xml; charset=\"utf-8\"\r\n"
		      "Content-Length: ",
		      path, inet_ntoa(dst->sin_addr), ntohs(dst->sin_port));

	*len_ptr = wpabuf_put(buf, 0);
	wpabuf_printf(buf,
		      "        \r\n"
		      "SOAPACTION: \"%s#%s\"\r\n"
		      "\r\n",
		      urn_wfawlanconfig, name);

	*body_ptr = wpabuf_put(buf, 0);

	wpabuf_put_str(buf, soap_prefix);
	wpabuf_printf(buf, "<u:%s xmlns:u=\"", name);
	wpabuf_put_str(buf, urn_wfawlanconfig);
	wpabuf_put_str(buf, "\">\n");
	if (encoded) {
		wpabuf_printf(buf, "<%s>%s</%s>\n",
			      arg_name, (char *) encoded, arg_name);
		os_free(encoded);
	}

	return buf;
}