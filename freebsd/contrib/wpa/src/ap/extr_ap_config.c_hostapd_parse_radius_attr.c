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
struct hostapd_radius_attr {void* val; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  hexstr2bin (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  os_free (struct hostapd_radius_attr*) ; 
 char* os_strchr (char const*,char) ; 
 size_t os_strlen (char const*) ; 
 struct hostapd_radius_attr* os_zalloc (int) ; 
 void* wpabuf_alloc (int) ; 
 void* wpabuf_alloc_copy (char const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_free (void*) ; 
 int /*<<< orphan*/  wpabuf_put (void*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (void*,int /*<<< orphan*/ ) ; 

struct hostapd_radius_attr * hostapd_parse_radius_attr(const char *value)
{
	const char *pos;
	char syntax;
	struct hostapd_radius_attr *attr;
	size_t len;

	attr = os_zalloc(sizeof(*attr));
	if (!attr)
		return NULL;

	attr->type = atoi(value);

	pos = os_strchr(value, ':');
	if (!pos) {
		attr->val = wpabuf_alloc(1);
		if (!attr->val) {
			os_free(attr);
			return NULL;
		}
		wpabuf_put_u8(attr->val, 0);
		return attr;
	}

	pos++;
	if (pos[0] == '\0' || pos[1] != ':') {
		os_free(attr);
		return NULL;
	}
	syntax = *pos++;
	pos++;

	switch (syntax) {
	case 's':
		attr->val = wpabuf_alloc_copy(pos, os_strlen(pos));
		break;
	case 'x':
		len = os_strlen(pos);
		if (len & 1)
			break;
		len /= 2;
		attr->val = wpabuf_alloc(len);
		if (!attr->val)
			break;
		if (hexstr2bin(pos, wpabuf_put(attr->val, len), len) < 0) {
			wpabuf_free(attr->val);
			os_free(attr);
			return NULL;
		}
		break;
	case 'd':
		attr->val = wpabuf_alloc(4);
		if (attr->val)
			wpabuf_put_be32(attr->val, atoi(pos));
		break;
	default:
		os_free(attr);
		return NULL;
	}

	if (!attr->val) {
		os_free(attr);
		return NULL;
	}

	return attr;
}