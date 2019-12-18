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
typedef  int /*<<< orphan*/  u32 ;
struct radius_msg {int dummy; } ;
struct extra_radius_attr {int syntax; char* data; int type; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t RADIUS_MAX_ATTR_LEN ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  hexstr2bin (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char*) ; 
 size_t os_strlen (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  radius_msg_add_attr (struct radius_msg*,int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int add_extra_attr(struct radius_msg *msg,
			  struct extra_radius_attr *attr)
{
	size_t len;
	char *pos;
	u32 val;
	char buf[RADIUS_MAX_ATTR_LEN + 1];

	switch (attr->syntax) {
	case 's':
		os_snprintf(buf, sizeof(buf), "%s", attr->data);
		len = os_strlen(buf);
		break;
	case 'n':
		buf[0] = '\0';
		len = 1;
		break;
	case 'x':
		pos = attr->data;
		if (pos[0] == '0' && pos[1] == 'x')
			pos += 2;
		len = os_strlen(pos);
		if ((len & 1) || (len / 2) > RADIUS_MAX_ATTR_LEN) {
			printf("Invalid extra attribute hexstring\n");
			return -1;
		}
		len /= 2;
		if (hexstr2bin(pos, (u8 *) buf, len) < 0) {
			printf("Invalid extra attribute hexstring\n");
			return -1;
		}
		break;
	case 'd':
		val = htonl(atoi(attr->data));
		os_memcpy(buf, &val, 4);
		len = 4;
		break;
	default:
		printf("Incorrect extra attribute syntax specification\n");
		return -1;
	}

	if (!radius_msg_add_attr(msg, attr->type, (u8 *) buf, len)) {
		printf("Could not add attribute %d\n", attr->type);
		return -1;
	}

	return 0;
}