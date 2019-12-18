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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int hex2chr (char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,unsigned char) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char const*,unsigned char) ; 

__attribute__((used)) static char *url_decode_internal(const char **query, int len,
				 const char *stop_at, struct strbuf *out,
				 int decode_plus)
{
	const char *q = *query;

	while (len) {
		unsigned char c = *q;

		if (!c)
			break;
		if (stop_at && strchr(stop_at, c)) {
			q++;
			len--;
			break;
		}

		if (c == '%' && (len < 0 || len >= 3)) {
			int val = hex2chr(q + 1);
			if (0 < val) {
				strbuf_addch(out, val);
				q += 3;
				len -= 3;
				continue;
			}
		}

		if (decode_plus && c == '+')
			strbuf_addch(out, ' ');
		else
			strbuf_addch(out, c);
		q++;
		len--;
	}
	*query = q;
	return strbuf_detach(out, NULL);
}