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
struct wpa_supplicant {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct wpa_ctrl_dst {int debug_level; int errors; int /*<<< orphan*/  addrlen; TYPE_1__ addr; struct wpa_ctrl_dst* next; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  levelstr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,...) ; 
 int os_strlen (char*) ; 
 scalar_t__ sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_detach (struct wpa_ctrl_dst**,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_supplicant_ctrl_iface_send(struct wpa_supplicant *wpa_s,
					   const char *ifname, int sock,
					   struct wpa_ctrl_dst **head,
					   int level, const char *buf,
					   size_t len)
{
	struct wpa_ctrl_dst *dst, *next;
	char levelstr[64];
	int idx;
	char *sbuf;
	int llen;
#ifdef CONFIG_CTRL_IFACE_UDP_IPV6
	char addr[INET6_ADDRSTRLEN];
#endif /* CONFIG_CTRL_IFACE_UDP_IPV6 */

	dst = *head;
	if (sock < 0 || dst == NULL)
		return;

	if (ifname)
		os_snprintf(levelstr, sizeof(levelstr), "IFACE=%s <%d>",
			    ifname, level);
	else
		os_snprintf(levelstr, sizeof(levelstr), "<%d>", level);

	llen = os_strlen(levelstr);
	sbuf = os_malloc(llen + len);
	if (sbuf == NULL)
		return;

	os_memcpy(sbuf, levelstr, llen);
	os_memcpy(sbuf + llen, buf, len);

	idx = 0;
	while (dst) {
		next = dst->next;
		if (level >= dst->debug_level) {
#ifdef CONFIG_CTRL_IFACE_UDP_IPV6
			wpa_printf(MSG_DEBUG, "CTRL_IFACE monitor send %s:%d",
				   inet_ntop(AF_INET6, &dst->addr.sin6_addr,
					     addr, sizeof(dst->addr)),
				   ntohs(dst->addr.sin6_port));
#else /* CONFIG_CTRL_IFACE_UDP_IPV6 */
			wpa_printf(MSG_DEBUG, "CTRL_IFACE monitor send %s:%d",
				   inet_ntoa(dst->addr.sin_addr),
				   ntohs(dst->addr.sin_port));
#endif /* CONFIG_CTRL_IFACE_UDP_IPV6 */
			if (sendto(sock, sbuf, llen + len, 0,
				   (struct sockaddr *) &dst->addr,
				   sizeof(dst->addr)) < 0) {
				wpa_printf(MSG_ERROR,
					   "sendto(CTRL_IFACE monitor): %s",
					   strerror(errno));
				dst->errors++;
				if (dst->errors > 10) {
					wpa_supplicant_ctrl_iface_detach(
						head, &dst->addr,
						dst->addrlen);
				}
			} else
				dst->errors = 0;
		}
		idx++;
		dst = next;
	}
	os_free(sbuf);
}