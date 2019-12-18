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
typedef  char u8 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,char) ; 

void xml_data_encode(struct wpabuf *buf, const char *data, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		u8 c = ((u8 *) data)[i];
		if (c == '<') {
			wpabuf_put_str(buf, "&lt;");
			continue;
		}
		if (c == '>') {
			wpabuf_put_str(buf, "&gt;");
			continue;
		}
		if (c == '&') {
			wpabuf_put_str(buf, "&amp;");
			continue;
		}
		if (c == '\'') {
			wpabuf_put_str(buf, "&apos;");
			continue;
		}
		if (c == '"') {
			wpabuf_put_str(buf, "&quot;");
			continue;
		}
		/*
		 * We could try to represent control characters using the
		 * sequence: &#x; where x is replaced by a hex numeral, but not
		 * clear why we would do this.
		 */
		wpabuf_put_u8(buf, c);
	}
}