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
struct hostent {char* h_name; int h_addrtype; int h_length; char** h_aliases; char** h_addr_list; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static void
sdump_hostent(struct hostent *ht, char *buffer, size_t buflen)
{
	char **cp;
	size_t i;
	int written;

	written = snprintf(buffer, buflen, "%s %d %d",
		ht->h_name, ht->h_addrtype, ht->h_length);
	buffer += written;
	if (written > (int)buflen)
		return;
	buflen -= written;

	if (ht->h_aliases != NULL) {
		if (*(ht->h_aliases) != NULL) {
			for (cp = ht->h_aliases; *cp; ++cp) {
				written = snprintf(buffer, buflen, " %s",*cp);
				buffer += written;
				if (written > (int)buflen)
					return;
				buflen -= written;

				if (buflen == 0)
					return;
			}
		} else {
			written = snprintf(buffer, buflen, " noaliases");
			buffer += written;
			if (written > (int)buflen)
				return;
			buflen -= written;
		}
	} else {
		written = snprintf(buffer, buflen, " (null)");
		buffer += written;
		if (written > (int)buflen)
			return;
		buflen -= written;
	}

	written = snprintf(buffer, buflen, " : ");
	buffer += written;
	if (written > (int)buflen)
		return;
	buflen -= written;

	if (ht->h_addr_list != NULL) {
		if (*(ht->h_addr_list) != NULL) {
			for (cp = ht->h_addr_list; *cp; ++cp) {
				for (i = 0; i < (size_t)ht->h_length; ++i) {
					written = snprintf(buffer, buflen,
					    i + 1 != (size_t)ht->h_length ?
					        "%d." : "%d",
					    (unsigned char)(*cp)[i]);
					buffer += written;
					if (written > (int)buflen)
						return;
					buflen -= written;

					if (buflen == 0)
						return;
				}

				if (*(cp + 1)) {
					written = snprintf(buffer, buflen,
					    " ");
					buffer += written;
					if (written > (int)buflen)
						return;
					buflen -= written;
				}
			}
		} else {
			written = snprintf(buffer, buflen, " noaddrs");
			buffer += written;
			if (written > (int)buflen)
				return;
			buflen -= written;
		}
	} else {
		written = snprintf(buffer, buflen, " (null)");
		buffer += written;
		if (written > (int)buflen)
			return;
		buflen -= written;
	}
}