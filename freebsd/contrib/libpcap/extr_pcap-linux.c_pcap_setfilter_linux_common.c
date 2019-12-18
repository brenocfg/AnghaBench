#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sock_fprog {int /*<<< orphan*/ * filter; scalar_t__ len; } ;
struct pcap_linux {int filter_in_userland; } ;
struct bpf_program {int dummy; } ;
struct TYPE_8__ {scalar_t__ bf_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  errbuf; TYPE_1__ fcode; struct pcap_linux* priv; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 scalar_t__ ENOPROTOOPT ; 
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ USHRT_MAX ; 
 scalar_t__ errno ; 
 int fix_program (TYPE_2__*,struct sock_fprog*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ install_bpf_program (TYPE_2__*,struct bpf_program*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 char* pcap_strerror (scalar_t__) ; 
 int reset_kernel_filter (TYPE_2__*) ; 
 int set_kernel_filter (TYPE_2__*,struct sock_fprog*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcap_setfilter_linux_common(pcap_t *handle, struct bpf_program *filter,
    int is_mmapped)
{
	struct pcap_linux *handlep;
#ifdef SO_ATTACH_FILTER
	struct sock_fprog	fcode;
	int			can_filter_in_kernel;
	int			err = 0;
#endif

	if (!handle)
		return -1;
	if (!filter) {
	        strlcpy(handle->errbuf, "setfilter: No filter specified",
			PCAP_ERRBUF_SIZE);
		return -1;
	}

	handlep = handle->priv;

	/* Make our private copy of the filter */

	if (install_bpf_program(handle, filter) < 0)
		/* install_bpf_program() filled in errbuf */
		return -1;

	/*
	 * Run user level packet filter by default. Will be overriden if
	 * installing a kernel filter succeeds.
	 */
	handlep->filter_in_userland = 1;

	/* Install kernel level filter if possible */

#ifdef SO_ATTACH_FILTER
#ifdef USHRT_MAX
	if (handle->fcode.bf_len > USHRT_MAX) {
		/*
		 * fcode.len is an unsigned short for current kernel.
		 * I have yet to see BPF-Code with that much
		 * instructions but still it is possible. So for the
		 * sake of correctness I added this check.
		 */
		fprintf(stderr, "Warning: Filter too complex for kernel\n");
		fcode.len = 0;
		fcode.filter = NULL;
		can_filter_in_kernel = 0;
	} else
#endif /* USHRT_MAX */
	{
		/*
		 * Oh joy, the Linux kernel uses struct sock_fprog instead
		 * of struct bpf_program and of course the length field is
		 * of different size. Pointed out by Sebastian
		 *
		 * Oh, and we also need to fix it up so that all "ret"
		 * instructions with non-zero operands have MAXIMUM_SNAPLEN
		 * as the operand if we're not capturing in memory-mapped
		 * mode, and so that, if we're in cooked mode, all memory-
		 * reference instructions use special magic offsets in
		 * references to the link-layer header and assume that the
		 * link-layer payload begins at 0; "fix_program()" will do
		 * that.
		 */
		switch (fix_program(handle, &fcode, is_mmapped)) {

		case -1:
		default:
			/*
			 * Fatal error; just quit.
			 * (The "default" case shouldn't happen; we
			 * return -1 for that reason.)
			 */
			return -1;

		case 0:
			/*
			 * The program performed checks that we can't make
			 * work in the kernel.
			 */
			can_filter_in_kernel = 0;
			break;

		case 1:
			/*
			 * We have a filter that'll work in the kernel.
			 */
			can_filter_in_kernel = 1;
			break;
		}
	}

	/*
	 * NOTE: at this point, we've set both the "len" and "filter"
	 * fields of "fcode".  As of the 2.6.32.4 kernel, at least,
	 * those are the only members of the "sock_fprog" structure,
	 * so we initialize every member of that structure.
	 *
	 * If there is anything in "fcode" that is not initialized,
	 * it is either a field added in a later kernel, or it's
	 * padding.
	 *
	 * If a new field is added, this code needs to be updated
	 * to set it correctly.
	 *
	 * If there are no other fields, then:
	 *
	 *	if the Linux kernel looks at the padding, it's
	 *	buggy;
	 *
	 *	if the Linux kernel doesn't look at the padding,
	 *	then if some tool complains that we're passing
	 *	uninitialized data to the kernel, then the tool
	 *	is buggy and needs to understand that it's just
	 *	padding.
	 */
	if (can_filter_in_kernel) {
		if ((err = set_kernel_filter(handle, &fcode)) == 0)
		{
			/*
			 * Installation succeded - using kernel filter,
			 * so userland filtering not needed.
			 */
			handlep->filter_in_userland = 0;
		}
		else if (err == -1)	/* Non-fatal error */
		{
			/*
			 * Print a warning if we weren't able to install
			 * the filter for a reason other than "this kernel
			 * isn't configured to support socket filters.
			 */
			if (errno != ENOPROTOOPT && errno != EOPNOTSUPP) {
				fprintf(stderr,
				    "Warning: Kernel filter failed: %s\n",
					pcap_strerror(errno));
			}
		}
	}

	/*
	 * If we're not using the kernel filter, get rid of any kernel
	 * filter that might've been there before, e.g. because the
	 * previous filter could work in the kernel, or because some other
	 * code attached a filter to the socket by some means other than
	 * calling "pcap_setfilter()".  Otherwise, the kernel filter may
	 * filter out packets that would pass the new userland filter.
	 */
	if (handlep->filter_in_userland) {
		if (reset_kernel_filter(handle) == -1) {
			pcap_fmt_errmsg_for_errno(handle->errbuf,
			    PCAP_ERRBUF_SIZE, errno,
			    "can't remove kernel filter");
			err = -2;	/* fatal error */
		}
	}

	/*
	 * Free up the copy of the filter that was made by "fix_program()".
	 */
	if (fcode.filter != NULL)
		free(fcode.filter);

	if (err == -2)
		/* Fatal error */
		return -1;
#endif /* SO_ATTACH_FILTER */

	return 0;
}