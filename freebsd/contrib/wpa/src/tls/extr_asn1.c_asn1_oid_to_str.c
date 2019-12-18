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
struct asn1_oid {size_t len; int /*<<< orphan*/ * oid; } ;

/* Variables and functions */
 int os_snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

void asn1_oid_to_str(const struct asn1_oid *oid, char *buf, size_t len)
{
	char *pos = buf;
	size_t i;
	int ret;

	if (len == 0)
		return;

	buf[0] = '\0';

	for (i = 0; i < oid->len; i++) {
		ret = os_snprintf(pos, buf + len - pos,
				  "%s%lu",
				  i == 0 ? "" : ".", oid->oid[i]);
		if (os_snprintf_error(buf + len - pos, ret))
			break;
		pos += ret;
	}
	buf[len - 1] = '\0';
}