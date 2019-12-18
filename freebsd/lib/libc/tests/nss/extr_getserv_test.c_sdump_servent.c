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
struct servent {char* s_name; char* s_proto; char** s_aliases; int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 
 int snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static void
sdump_servent(struct servent *serv, char *buffer, size_t buflen)
{
	char **cp;
	int written;

	written = snprintf(buffer, buflen, "%s %d %s",
		serv->s_name, ntohs(serv->s_port), serv->s_proto);
	buffer += written;
	if (written > (int)buflen)
		return;
	buflen -= written;

	if (serv->s_aliases != NULL) {
		if (*(serv->s_aliases) != NULL) {
			for (cp = serv->s_aliases; *cp; ++cp) {
				written = snprintf(buffer, buflen, " %s", *cp);
				buffer += written;
				if (written > (int)buflen)
					return;
				buflen -= written;

				if (buflen == 0)
					return;
			}
		} else
			snprintf(buffer, buflen, " noaliases");
	} else
		snprintf(buffer, buflen, " (null)");
}