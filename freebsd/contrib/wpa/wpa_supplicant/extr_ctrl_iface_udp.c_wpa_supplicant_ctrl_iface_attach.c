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
struct wpa_ctrl_dst {struct wpa_ctrl_dst* next; int /*<<< orphan*/  debug_level; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct sockaddr_in*,int) ; 
 struct wpa_ctrl_dst* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_attach(struct wpa_ctrl_dst **head,
#ifdef CONFIG_CTRL_IFACE_UDP_IPV6
					    struct sockaddr_in6 *from,
#else /* CONFIG_CTRL_IFACE_UDP_IPV6 */
					    struct sockaddr_in *from,
#endif /* CONFIG_CTRL_IFACE_UDP_IPV6 */
					    socklen_t fromlen)
{
	struct wpa_ctrl_dst *dst;
#ifdef CONFIG_CTRL_IFACE_UDP_IPV6
	char addr[INET6_ADDRSTRLEN];
#endif /* CONFIG_UDP_IPV6 */

	dst = os_zalloc(sizeof(*dst));
	if (dst == NULL)
		return -1;
	os_memcpy(&dst->addr, from, sizeof(*from));
	dst->addrlen = fromlen;
	dst->debug_level = MSG_INFO;
	dst->next = *head;
	*head = dst;
#ifdef CONFIG_CTRL_IFACE_UDP_IPV6
	wpa_printf(MSG_DEBUG, "CTRL_IFACE monitor attached %s:%d",
		   inet_ntop(AF_INET6, &from->sin6_addr, addr, sizeof(*from)),
		   ntohs(from->sin6_port));
#else /* CONFIG_CTRL_IFACE_UDP_IPV6 */
	wpa_printf(MSG_DEBUG, "CTRL_IFACE monitor attached %s:%d",
		   inet_ntoa(from->sin_addr), ntohs(from->sin_port));
#endif /* CONFIG_CTRL_IFACE_UDP_IPV6 */
	return 0;
}