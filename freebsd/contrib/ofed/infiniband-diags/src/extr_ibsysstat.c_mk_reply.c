#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* model; char* mhz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int) ; 
 int /*<<< orphan*/  IBWARN (char*) ; 
#define  IB_CPUINFO_ATTR 130 
#define  IB_HOSTINFO_ATTR 129 
#define  IB_PING_ATTR 128 
 TYPE_1__* cpus ; 
 int /*<<< orphan*/  getdomainname (char*,int) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int host_ncpu ; 
 int snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int mk_reply(int attr, void *data, int sz)
{
	char *s = data;
	int n, i, ret = 0;

	switch (attr) {
	case IB_PING_ATTR:
		break;		/* nothing to do here, just reply */
	case IB_HOSTINFO_ATTR:
		if (gethostname(s, sz) < 0)
			snprintf(s, sz, "?hostname?");
		s[sz - 1] = 0;
		if ((n = strlen(s)) >= sz - 1) {
			ret = sz;
			break;
		}
		s[n] = '.';
		s += n + 1;
		sz -= n + 1;
		ret += n + 1;
		if (getdomainname(s, sz) < 0)
			snprintf(s, sz, "?domainname?");
		if ((n = strlen(s)) == 0)
			s[-1] = 0;	/* no domain */
		else
			ret += n;
		break;
	case IB_CPUINFO_ATTR:
		s[0] = '\0';
		for (i = 0; i < host_ncpu && sz > 0; i++) {
			n = snprintf(s, sz, "cpu %d: model %s MHZ %s\n",
				     i, cpus[i].model, cpus[i].mhz);
			if (n >= sz) {
				IBWARN("cpuinfo truncated");
				ret = sz;
				break;
			}
			sz -= n;
			s += n;
			ret += n;
		}
		ret++;
		break;
	default:
		DEBUG("unknown attr %d", attr);
	}
	return ret;
}