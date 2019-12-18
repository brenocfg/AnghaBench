#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct pcap_dag {int dummy; } ;
struct TYPE_5__ {int tstamp_precision_count; int /*<<< orphan*/ * tstamp_precision_list; int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 long DAG_MAX_BOARDS ; 
 long DAG_STREAM_MAX ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_MICRO ; 
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_NANO ; 
 int /*<<< orphan*/  dag_activate ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pcap_close (TYPE_1__*) ; 
 TYPE_1__* pcap_create_common (char*,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 
 long strtol (char const*,char**,int) ; 

pcap_t *dag_create(const char *device, char *ebuf, int *is_ours)
{
	const char *cp;
	char *cpend;
	long devnum;
	pcap_t *p;
	long stream = 0;

	/* Does this look like a DAG device? */
	cp = strrchr(device, '/');
	if (cp == NULL)
		cp = device;
	/* Does it begin with "dag"? */
	if (strncmp(cp, "dag", 3) != 0) {
		/* Nope, doesn't begin with "dag" */
		*is_ours = 0;
		return NULL;
	}
	/* Yes - is "dag" followed by a number from 0 to DAG_MAX_BOARDS-1 */
	cp += 3;
	devnum = strtol(cp, &cpend, 10);
	if (*cpend == ':') {
		/* Followed by a stream number. */
		stream = strtol(++cpend, &cpend, 10);
	}

	if (cpend == cp || *cpend != '\0') {
		/* Not followed by a number. */
		*is_ours = 0;
		return NULL;
	}

	if (devnum < 0 || devnum >= DAG_MAX_BOARDS) {
		/* Followed by a non-valid number. */
		*is_ours = 0;
		return NULL;
	}

	if (stream <0 || stream >= DAG_STREAM_MAX) {
		/* Followed by a non-valid stream number. */
		*is_ours = 0;
		return NULL;
	}

	/* OK, it's probably ours. */
	*is_ours = 1;

	p = pcap_create_common(ebuf, sizeof (struct pcap_dag));
	if (p == NULL)
		return NULL;

	p->activate_op = dag_activate;

	/*
	 * We claim that we support microsecond and nanosecond time
	 * stamps.
	 *
	 * XXX Our native precision is 2^-32s, but libpcap doesn't support
	 * power of two precisions yet. We can convert to either MICRO or NANO.
	 */
	p->tstamp_precision_count = 2;
	p->tstamp_precision_list = malloc(2 * sizeof(u_int));
	if (p->tstamp_precision_list == NULL) {
		pcap_fmt_errmsg_for_errno(ebuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		pcap_close(p);
		return NULL;
	}
	p->tstamp_precision_list[0] = PCAP_TSTAMP_PRECISION_MICRO;
	p->tstamp_precision_list[1] = PCAP_TSTAMP_PRECISION_NANO;
	return p;
}