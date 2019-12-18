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
typedef  int u_int ;

/* Variables and functions */
 int PROTO_UNDEF ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ pcap_nametoport (char*,int*,int*) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

int
pcap_nametoportrange(const char *name, int *port1, int *port2, int *proto)
{
	u_int p1, p2;
	char *off, *cpy;
	int save_proto;

	if (sscanf(name, "%d-%d", &p1, &p2) != 2) {
		if ((cpy = strdup(name)) == NULL)
			return 0;

		if ((off = strchr(cpy, '-')) == NULL) {
			free(cpy);
			return 0;
		}

		*off = '\0';

		if (pcap_nametoport(cpy, port1, proto) == 0) {
			free(cpy);
			return 0;
		}
		save_proto = *proto;

		if (pcap_nametoport(off + 1, port2, proto) == 0) {
			free(cpy);
			return 0;
		}
		free(cpy);

		if (*proto != save_proto)
			*proto = PROTO_UNDEF;
	} else {
		*port1 = p1;
		*port2 = p2;
		*proto = PROTO_UNDEF;
	}

	return 1;
}