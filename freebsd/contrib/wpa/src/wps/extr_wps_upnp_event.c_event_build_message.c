#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wps_event_ {int subscriber_sequence; int /*<<< orphan*/  data; TYPE_2__* s; TYPE_1__* addr; } ;
struct wpabuf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  uuid; } ;
struct TYPE_3__ {int path; int domain_and_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_strlen (char*) ; 
 int /*<<< orphan*/  uuid_bin2str (int /*<<< orphan*/ ,char*,int) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 scalar_t__ wpabuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,int) ; 
 char* wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static struct wpabuf * event_build_message(struct wps_event_ *e)
{
	struct wpabuf *buf;
	char *b;

	buf = wpabuf_alloc(1000 + wpabuf_len(e->data));
	if (buf == NULL)
		return NULL;
	wpabuf_printf(buf, "NOTIFY %s HTTP/1.1\r\n", e->addr->path);
	wpabuf_put_str(buf, "SERVER: Unspecified, UPnP/1.0, Unspecified\r\n");
	wpabuf_printf(buf, "HOST: %s\r\n", e->addr->domain_and_port);
	wpabuf_put_str(buf, "CONTENT-TYPE: text/xml; charset=\"utf-8\"\r\n"
		       "NT: upnp:event\r\n"
		       "NTS: upnp:propchange\r\n");
	wpabuf_put_str(buf, "SID: uuid:");
	b = wpabuf_put(buf, 0);
	uuid_bin2str(e->s->uuid, b, 80);
	wpabuf_put(buf, os_strlen(b));
	wpabuf_put_str(buf, "\r\n");
	wpabuf_printf(buf, "SEQ: %u\r\n", e->subscriber_sequence);
	wpabuf_printf(buf, "CONTENT-LENGTH: %d\r\n",
		      (int) wpabuf_len(e->data));
	wpabuf_put_str(buf, "\r\n"); /* terminating empty line */
	wpabuf_put_buf(buf, e->data);
	return buf;
}