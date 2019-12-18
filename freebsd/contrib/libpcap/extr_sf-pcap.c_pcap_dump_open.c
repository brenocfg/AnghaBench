#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int linktype_ext; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  linktype; int /*<<< orphan*/  activated; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  pcap_dumper_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int dlt_to_linktype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * pcap_setup_dump (TYPE_1__*,int,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * stdout ; 

pcap_dumper_t *
pcap_dump_open(pcap_t *p, const char *fname)
{
	FILE *f;
	int linktype;

	/*
	 * If this pcap_t hasn't been activated, it doesn't have a
	 * link-layer type, so we can't use it.
	 */
	if (!p->activated) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "%s: not-yet-activated pcap_t passed to pcap_dump_open",
		    fname);
		return (NULL);
	}
	linktype = dlt_to_linktype(p->linktype);
	if (linktype == -1) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "%s: link-layer type %d isn't supported in savefiles",
		    fname, p->linktype);
		return (NULL);
	}
	linktype |= p->linktype_ext;

	if (fname == NULL) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "A null pointer was supplied as the file name");
		return NULL;
	}
	if (fname[0] == '-' && fname[1] == '\0') {
		f = stdout;
		fname = "standard output";
	} else {
		/*
		 * "b" is supported as of C90, so *all* UN*Xes should
		 * support it, even though it does nothing.  It's
		 * required on Windows, as the file is a binary file
		 * and must be written in binary mode.
		 */
		f = fopen(fname, "wb");
		if (f == NULL) {
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "%s", fname);
			return (NULL);
		}
	}
	return (pcap_setup_dump(p, linktype, f, fname));
}