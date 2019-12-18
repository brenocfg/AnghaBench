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
struct pcap_pf {int filtering_in_kernel; } ;
struct bpf_version {scalar_t__ bv_major; scalar_t__ bv_minor; } ;
struct bpf_program {int dummy; } ;
struct TYPE_4__ {scalar_t__ cc; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; struct pcap_pf* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIOCSETF ; 
 int /*<<< orphan*/  BIOCVERSION ; 
 scalar_t__ BPF_MAJOR_VERSION ; 
 scalar_t__ BPF_MINOR_VERSION ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ install_bpf_program (TYPE_1__*,struct bpf_program*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
pcap_setfilter_pf(pcap_t *p, struct bpf_program *fp)
{
	struct pcap_pf *pf = p->priv;
	struct bpf_version bv;

	/*
	 * See if BIOCVERSION works.  If not, we assume the kernel doesn't
	 * support BPF-style filters (it's not documented in the bpf(7)
	 * or packetfiler(7) man pages, but the code used to fail if
	 * BIOCSETF worked but BIOCVERSION didn't, and I've seen it do
	 * kernel filtering in DU 4.0, so presumably BIOCVERSION works
	 * there, at least).
	 */
	if (ioctl(p->fd, BIOCVERSION, (caddr_t)&bv) >= 0) {
		/*
		 * OK, we have the version of the BPF interpreter;
		 * is it the same major version as us, and the same
		 * or better minor version?
		 */
		if (bv.bv_major == BPF_MAJOR_VERSION &&
		    bv.bv_minor >= BPF_MINOR_VERSION) {
			/*
			 * Yes.  Try to install the filter.
			 */
			if (ioctl(p->fd, BIOCSETF, (caddr_t)fp) < 0) {
				pcap_fmt_errmsg_for_errno(p->errbuf,
				    sizeof(p->errbuf), errno, "BIOCSETF");
				return (-1);
			}

			/*
			 * OK, that succeeded.  We're doing filtering in
			 * the kernel.  (We assume we don't have a
			 * userland filter installed - that'd require
			 * a previous version check to have failed but
			 * this one to succeed.)
			 *
			 * XXX - this message should be supplied to the
			 * application as a warning of some sort,
			 * except that if it's a GUI application, it's
			 * not clear that it should be displayed in
			 * a window to annoy the user.
			 */
			fprintf(stderr, "tcpdump: Using kernel BPF filter\n");
			pf->filtering_in_kernel = 1;

			/*
			 * Discard any previously-received packets,
			 * as they might have passed whatever filter
			 * was formerly in effect, but might not pass
			 * this filter (BIOCSETF discards packets buffered
			 * in the kernel, so you can lose packets in any
			 * case).
			 */
			p->cc = 0;
			return (0);
		}

		/*
		 * We can't use the kernel's BPF interpreter; don't give
		 * up, just log a message and be inefficient.
		 *
		 * XXX - this should really be supplied to the application
		 * as a warning of some sort.
		 */
		fprintf(stderr,
	    "tcpdump: Requires BPF language %d.%d or higher; kernel is %d.%d\n",
		    BPF_MAJOR_VERSION, BPF_MINOR_VERSION,
		    bv.bv_major, bv.bv_minor);
	}

	/*
	 * We couldn't do filtering in the kernel; do it in userland.
	 */
	if (install_bpf_program(p, fp) < 0)
		return (-1);

	/*
	 * XXX - this message should be supplied by the application as
	 * a warning of some sort.
	 */
	fprintf(stderr, "tcpdump: Filtering in user process\n");
	pf->filtering_in_kernel = 0;
	return (0);
}