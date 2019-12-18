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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ os_strncasecmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int* wpabuf_head (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 

int domain_name_list_contains(struct wpabuf *domain_names,
			      const char *domain, int exact_match)
{
	const u8 *pos, *end;
	size_t len;

	len = os_strlen(domain);
	pos = wpabuf_head(domain_names);
	end = pos + wpabuf_len(domain_names);

	while (end - pos > 1) {
		u8 elen;

		elen = *pos++;
		if (elen > end - pos)
			break;

		wpa_hexdump_ascii(MSG_DEBUG, "Interworking: AP domain name",
				  pos, elen);
		if (elen == len &&
		    os_strncasecmp(domain, (const char *) pos, len) == 0)
			return 1;
		if (!exact_match && elen > len && pos[elen - len - 1] == '.') {
			const char *ap = (const char *) pos;
			int offset = elen - len;

			if (os_strncasecmp(domain, ap + offset, len) == 0)
				return 1;
		}

		pos += elen;
	}

	return 0;
}