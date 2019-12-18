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
typedef  scalar_t__ u_short ;
struct servent {int /*<<< orphan*/  s_port; } ;
typedef  int /*<<< orphan*/  port_range ;

/* Variables and functions */
 scalar_t__ GETNUMPORTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETLOPORT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SETNUMPORTS (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 struct servent* getservbyname (char const*,char const*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,scalar_t__*,scalar_t__*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strtol (char const*,char**,int) ; 

int StrToPortRange (const char* str, const char* proto, port_range *portRange)
{
	const char*	sep;
	struct servent*	sp;
	char*		end;
	u_short         loPort;
	u_short         hiPort;
	
	/* First see if this is a service, return corresponding port if so. */
	sp = getservbyname (str,proto);
	if (sp) {
	        SETLOPORT(*portRange, ntohs(sp->s_port));
		SETNUMPORTS(*portRange, 1);
		return 0;
	}
	        
	/* Not a service, see if it's a single port or port range. */
	sep = strchr (str, '-');
	if (sep == NULL) {
	        SETLOPORT(*portRange, strtol(str, &end, 10));
		if (end != str) {
		        /* Single port. */
		        SETNUMPORTS(*portRange, 1);
			return 0;
		}

		/* Error in port range field. */
		errx (1, "%s/%s: unknown service", str, proto);
	}

	/* Port range, get the values and sanity check. */
	sscanf (str, "%hu-%hu", &loPort, &hiPort);
	SETLOPORT(*portRange, loPort);
	SETNUMPORTS(*portRange, 0);	/* Error by default */
	if (loPort <= hiPort)
	        SETNUMPORTS(*portRange, hiPort - loPort + 1);

	if (GETNUMPORTS(*portRange) == 0)
	        errx (1, "invalid port range %s", str);

	return 0;
}