#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wps_er {int /*<<< orphan*/  multicast_sd; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  dest ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  UPNP_MULTICAST_ADDRESS ; 
 int /*<<< orphan*/  UPNP_MULTICAST_PORT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

void wps_er_send_ssdp_msearch(struct wps_er *er)
{
	struct wpabuf *msg;
	struct sockaddr_in dest;

	msg = wpabuf_alloc(500);
	if (msg == NULL)
		return;

	wpabuf_put_str(msg,
		       "M-SEARCH * HTTP/1.1\r\n"
		       "HOST: 239.255.255.250:1900\r\n"
		       "MAN: \"ssdp:discover\"\r\n"
		       "MX: 3\r\n"
		       "ST: urn:schemas-wifialliance-org:device:WFADevice:1"
		       "\r\n"
		       "\r\n");

	os_memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(UPNP_MULTICAST_ADDRESS);
	dest.sin_port = htons(UPNP_MULTICAST_PORT);

	if (sendto(er->multicast_sd, wpabuf_head(msg), wpabuf_len(msg), 0,
		   (struct sockaddr *) &dest, sizeof(dest)) < 0)
		wpa_printf(MSG_DEBUG, "WPS ER: M-SEARCH sendto failed: "
			   "%d (%s)", errno, strerror(errno));

	wpabuf_free(msg);
}