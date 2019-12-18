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
typedef  int /*<<< orphan*/  tunnel ;
struct radius_tunnel_attrs {scalar_t__ type; scalar_t__ medium_type; int vlanid; scalar_t__ tag_used; } ;
struct radius_msg {size_t attr_used; } ;
struct radius_attr_hdr {int length; int type; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  RADIUS_ATTR_EGRESS_VLANID 131 
#define  RADIUS_ATTR_TUNNEL_MEDIUM_TYPE 130 
#define  RADIUS_ATTR_TUNNEL_PRIVATE_GROUP_ID 129 
#define  RADIUS_ATTR_TUNNEL_TYPE 128 
 scalar_t__ RADIUS_TUNNEL_MEDIUM_TYPE_802 ; 
 int RADIUS_TUNNEL_TAGS ; 
 scalar_t__ RADIUS_TUNNEL_TYPE_VLAN ; 
 void* WPA_GET_BE24 (int const*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  cmp_int ; 
 int /*<<< orphan*/  os_memcpy (char*,int const*,size_t) ; 
 int /*<<< orphan*/  os_memset (struct radius_tunnel_attrs**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 

int radius_msg_get_vlanid(struct radius_msg *msg, int *untagged, int numtagged,
			  int *tagged)
{
	struct radius_tunnel_attrs tunnel[RADIUS_TUNNEL_TAGS], *tun;
	size_t i;
	struct radius_attr_hdr *attr = NULL;
	const u8 *data;
	char buf[10];
	size_t dlen;
	int j, taggedidx = 0, vlan_id;

	os_memset(&tunnel, 0, sizeof(tunnel));
	for (j = 0; j < numtagged; j++)
		tagged[j] = 0;
	*untagged = 0;

	for (i = 0; i < msg->attr_used; i++) {
		attr = radius_get_attr_hdr(msg, i);
		if (attr->length < sizeof(*attr))
			return -1;
		data = (const u8 *) (attr + 1);
		dlen = attr->length - sizeof(*attr);
		if (attr->length < 3)
			continue;
		if (data[0] >= RADIUS_TUNNEL_TAGS)
			tun = &tunnel[0];
		else
			tun = &tunnel[data[0]];

		switch (attr->type) {
		case RADIUS_ATTR_TUNNEL_TYPE:
			if (attr->length != 6)
				break;
			tun->tag_used++;
			tun->type = WPA_GET_BE24(data + 1);
			break;
		case RADIUS_ATTR_TUNNEL_MEDIUM_TYPE:
			if (attr->length != 6)
				break;
			tun->tag_used++;
			tun->medium_type = WPA_GET_BE24(data + 1);
			break;
		case RADIUS_ATTR_TUNNEL_PRIVATE_GROUP_ID:
			if (data[0] < RADIUS_TUNNEL_TAGS) {
				data++;
				dlen--;
			}
			if (dlen >= sizeof(buf))
				break;
			os_memcpy(buf, data, dlen);
			buf[dlen] = '\0';
			vlan_id = atoi(buf);
			if (vlan_id <= 0)
				break;
			tun->tag_used++;
			tun->vlanid = vlan_id;
			break;
		case RADIUS_ATTR_EGRESS_VLANID: /* RFC 4675 */
			if (attr->length != 6)
				break;
			vlan_id = WPA_GET_BE24(data + 1);
			if (vlan_id <= 0)
				break;
			if (data[0] == 0x32)
				*untagged = vlan_id;
			else if (data[0] == 0x31 && tagged &&
				 taggedidx < numtagged)
				tagged[taggedidx++] = vlan_id;
			break;
		}
	}

	/* Use tunnel with the lowest tag for untagged VLAN id */
	for (i = 0; i < RADIUS_TUNNEL_TAGS; i++) {
		tun = &tunnel[i];
		if (tun->tag_used &&
		    tun->type == RADIUS_TUNNEL_TYPE_VLAN &&
		    tun->medium_type == RADIUS_TUNNEL_MEDIUM_TYPE_802 &&
		    tun->vlanid > 0) {
			*untagged = tun->vlanid;
			break;
		}
	}

	if (taggedidx)
		qsort(tagged, taggedidx, sizeof(int), cmp_int);

	if (*untagged > 0 || taggedidx)
		return 1;
	return 0;
}