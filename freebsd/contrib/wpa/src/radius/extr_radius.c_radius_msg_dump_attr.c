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
struct radius_attr_type {char* name; int data_type; } ;
struct radius_attr_hdr {int length; int /*<<< orphan*/  type; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  RADIUS_ATTR_HEXDUMP 133 
#define  RADIUS_ATTR_INT32 132 
#define  RADIUS_ATTR_IP 131 
#define  RADIUS_ATTR_IPV6 130 
#define  RADIUS_ATTR_TEXT 129 
#define  RADIUS_ATTR_UNDIST 128 
 int WPA_GET_BE32 (unsigned char*) ; 
 int inet_ntoa (struct in_addr) ; 
 char* inet_ntop (int /*<<< orphan*/ ,struct in6_addr*,char*,int) ; 
 int /*<<< orphan*/  os_memcpy (struct in_addr*,unsigned char*,int) ; 
 int /*<<< orphan*/  printf_encode (char*,int,unsigned char*,int) ; 
 struct radius_attr_type* radius_get_attr_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,unsigned char*,int) ; 

__attribute__((used)) static void radius_msg_dump_attr(struct radius_attr_hdr *hdr)
{
	const struct radius_attr_type *attr;
	int len;
	unsigned char *pos;
	char buf[1000];

	attr = radius_get_attr_type(hdr->type);

	wpa_printf(MSG_INFO, "   Attribute %d (%s) length=%d",
		   hdr->type, attr ? attr->name : "?Unknown?", hdr->length);

	if (attr == NULL || hdr->length < sizeof(struct radius_attr_hdr))
		return;

	len = hdr->length - sizeof(struct radius_attr_hdr);
	pos = (unsigned char *) (hdr + 1);

	switch (attr->data_type) {
	case RADIUS_ATTR_TEXT:
		printf_encode(buf, sizeof(buf), pos, len);
		wpa_printf(MSG_INFO, "      Value: '%s'", buf);
		break;

	case RADIUS_ATTR_IP:
		if (len == 4) {
			struct in_addr addr;
			os_memcpy(&addr, pos, 4);
			wpa_printf(MSG_INFO, "      Value: %s",
				   inet_ntoa(addr));
		} else {
			wpa_printf(MSG_INFO, "      Invalid IP address length %d",
				   len);
		}
		break;

#ifdef CONFIG_IPV6
	case RADIUS_ATTR_IPV6:
		if (len == 16) {
			const char *atxt;
			struct in6_addr *addr = (struct in6_addr *) pos;
			atxt = inet_ntop(AF_INET6, addr, buf, sizeof(buf));
			wpa_printf(MSG_INFO, "      Value: %s",
				   atxt ? atxt : "?");
		} else {
			wpa_printf(MSG_INFO, "      Invalid IPv6 address length %d",
				   len);
		}
		break;
#endif /* CONFIG_IPV6 */

	case RADIUS_ATTR_HEXDUMP:
	case RADIUS_ATTR_UNDIST:
		wpa_snprintf_hex(buf, sizeof(buf), pos, len);
		wpa_printf(MSG_INFO, "      Value: %s", buf);
		break;

	case RADIUS_ATTR_INT32:
		if (len == 4)
			wpa_printf(MSG_INFO, "      Value: %u",
				   WPA_GET_BE32(pos));
		else
			wpa_printf(MSG_INFO, "      Invalid INT32 length %d",
				   len);
		break;

	default:
		break;
	}
}