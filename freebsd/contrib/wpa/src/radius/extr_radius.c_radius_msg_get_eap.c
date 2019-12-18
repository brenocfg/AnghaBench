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
struct radius_msg {size_t attr_used; } ;
struct radius_attr_hdr {scalar_t__ type; int length; } ;

/* Variables and functions */
 scalar_t__ RADIUS_ATTR_EAP_MESSAGE ; 
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,struct radius_attr_hdr*,int) ; 

struct wpabuf * radius_msg_get_eap(struct radius_msg *msg)
{
	struct wpabuf *eap;
	size_t len, i;
	struct radius_attr_hdr *attr;

	if (msg == NULL)
		return NULL;

	len = 0;
	for (i = 0; i < msg->attr_used; i++) {
		attr = radius_get_attr_hdr(msg, i);
		if (attr->type == RADIUS_ATTR_EAP_MESSAGE &&
		    attr->length > sizeof(struct radius_attr_hdr))
			len += attr->length - sizeof(struct radius_attr_hdr);
	}

	if (len == 0)
		return NULL;

	eap = wpabuf_alloc(len);
	if (eap == NULL)
		return NULL;

	for (i = 0; i < msg->attr_used; i++) {
		attr = radius_get_attr_hdr(msg, i);
		if (attr->type == RADIUS_ATTR_EAP_MESSAGE &&
		    attr->length > sizeof(struct radius_attr_hdr)) {
			int flen = attr->length - sizeof(*attr);
			wpabuf_put_data(eap, attr + 1, flen);
		}
	}

	return eap;
}