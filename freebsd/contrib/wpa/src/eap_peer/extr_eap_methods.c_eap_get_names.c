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
struct eap_method {int /*<<< orphan*/  name; struct eap_method* next; } ;

/* Variables and functions */
 struct eap_method* eap_methods ; 
 int os_snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

size_t eap_get_names(char *buf, size_t buflen)
{
	char *pos, *end;
	struct eap_method *m;
	int ret;

	if (buflen == 0)
		return 0;

	pos = buf;
	end = pos + buflen;

	for (m = eap_methods; m; m = m->next) {
		ret = os_snprintf(pos, end - pos, "%s%s",
				  m == eap_methods ? "" : " ", m->name);
		if (os_snprintf_error(end - pos, ret))
			break;
		pos += ret;
	}
	buf[buflen - 1] = '\0';

	return pos - buf;
}