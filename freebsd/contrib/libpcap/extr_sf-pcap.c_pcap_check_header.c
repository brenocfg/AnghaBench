#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct pcap_sf_pkthdr {int dummy; } ;
struct pcap_sf_patched_pkthdr {int dummy; } ;
struct pcap_sf {int hdrsize; void* lengths_swapped; void* scale_type; } ;
struct pcap_file_header {int version_major; int version_minor; scalar_t__ thiszone; scalar_t__ sigfigs; scalar_t__ snaplen; scalar_t__ linktype; scalar_t__ magic; } ;
struct TYPE_6__ {int tstamp_precision; } ;
struct TYPE_7__ {int swapped; int version_major; int version_minor; scalar_t__ tzoff; scalar_t__ snapshot; scalar_t__ linktype; int bufsize; int /*<<< orphan*/  cleanup_op; int /*<<< orphan*/ * buffer; TYPE_1__ opt; struct pcap_sf* priv; int /*<<< orphan*/  next_packet_op; int /*<<< orphan*/  linktype_ext; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  hdr ;
typedef  scalar_t__ bpf_u_int32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DLT_EN10MB ; 
 scalar_t__ KUZNETZOV_TCPDUMP_MAGIC ; 
 int /*<<< orphan*/  LT_LINKTYPE (scalar_t__) ; 
 int /*<<< orphan*/  LT_LINKTYPE_EXT (scalar_t__) ; 
 void* MAYBE_SWAPPED ; 
 void* NOT_SWAPPED ; 
 scalar_t__ NSEC_TCPDUMP_MAGIC ; 
 void* PASS_THROUGH ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
#define  PCAP_TSTAMP_PRECISION_MICRO 129 
#define  PCAP_TSTAMP_PRECISION_NANO 128 
 int PCAP_VERSION_MAJOR ; 
 int PCAP_VERSION_MINOR ; 
 void* SCALE_DOWN ; 
 void* SCALE_UP ; 
 scalar_t__ SWAPLONG (scalar_t__) ; 
 void* SWAPPED ; 
 void* SWAPSHORT (int) ; 
 scalar_t__ TCPDUMP_MAGIC ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ linktype_to_dlt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ max_snaplen_for_dlt (scalar_t__) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_next_packet ; 
 TYPE_2__* pcap_open_offline_common (char*,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sf_cleanup ; 

pcap_t *
pcap_check_header(bpf_u_int32 magic, FILE *fp, u_int precision, char *errbuf,
		  int *err)
{
	struct pcap_file_header hdr;
	size_t amt_read;
	pcap_t *p;
	int swapped = 0;
	struct pcap_sf *ps;

	/*
	 * Assume no read errors.
	 */
	*err = 0;

	/*
	 * Check whether the first 4 bytes of the file are the magic
	 * number for a pcap savefile, or for a byte-swapped pcap
	 * savefile.
	 */
	if (magic != TCPDUMP_MAGIC && magic != KUZNETZOV_TCPDUMP_MAGIC &&
	    magic != NSEC_TCPDUMP_MAGIC) {
		magic = SWAPLONG(magic);
		if (magic != TCPDUMP_MAGIC && magic != KUZNETZOV_TCPDUMP_MAGIC &&
		    magic != NSEC_TCPDUMP_MAGIC)
			return (NULL);	/* nope */
		swapped = 1;
	}

	/*
	 * They are.  Put the magic number in the header, and read
	 * the rest of the header.
	 */
	hdr.magic = magic;
	amt_read = fread(((char *)&hdr) + sizeof hdr.magic, 1,
	    sizeof(hdr) - sizeof(hdr.magic), fp);
	if (amt_read != sizeof(hdr) - sizeof(hdr.magic)) {
		if (ferror(fp)) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "error reading dump file");
		} else {
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "truncated dump file; tried to read %lu file header bytes, only got %lu",
			    (unsigned long)sizeof(hdr),
			    (unsigned long)amt_read);
		}
		*err = 1;
		return (NULL);
	}

	/*
	 * If it's a byte-swapped capture file, byte-swap the header.
	 */
	if (swapped) {
		hdr.version_major = SWAPSHORT(hdr.version_major);
		hdr.version_minor = SWAPSHORT(hdr.version_minor);
		hdr.thiszone = SWAPLONG(hdr.thiszone);
		hdr.sigfigs = SWAPLONG(hdr.sigfigs);
		hdr.snaplen = SWAPLONG(hdr.snaplen);
		hdr.linktype = SWAPLONG(hdr.linktype);
	}

	if (hdr.version_major < PCAP_VERSION_MAJOR) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "archaic pcap savefile format");
		*err = 1;
		return (NULL);
	}

	/*
	 * currently only versions 2.[0-4] are supported with
	 * the exception of 543.0 for DG/UX tcpdump.
	 */
	if (! ((hdr.version_major == PCAP_VERSION_MAJOR &&
		hdr.version_minor <= PCAP_VERSION_MINOR) ||
	       (hdr.version_major == 543 &&
		hdr.version_minor == 0))) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
			 "unsupported pcap savefile version %u.%u",
			 hdr.version_major, hdr.version_minor);
		*err = 1;
		return NULL;
	}

	/*
	 * OK, this is a good pcap file.
	 * Allocate a pcap_t for it.
	 */
	p = pcap_open_offline_common(errbuf, sizeof (struct pcap_sf));
	if (p == NULL) {
		/* Allocation failed. */
		*err = 1;
		return (NULL);
	}
	p->swapped = swapped;
	p->version_major = hdr.version_major;
	p->version_minor = hdr.version_minor;
	p->tzoff = hdr.thiszone;
	p->snapshot = hdr.snaplen;
	if (p->snapshot <= 0) {
		/*
		 * Bogus snapshot length; use the maximum for this
		 * link-layer type as a fallback.
		 *
		 * XXX - the only reason why snapshot is signed is
		 * that pcap_snapshot() returns an int, not an
		 * unsigned int.
		 */
		p->snapshot = max_snaplen_for_dlt(hdr.linktype);
	}
	p->linktype = linktype_to_dlt(LT_LINKTYPE(hdr.linktype));
	p->linktype_ext = LT_LINKTYPE_EXT(hdr.linktype);

	p->next_packet_op = pcap_next_packet;

	ps = p->priv;

	p->opt.tstamp_precision = precision;

	/*
	 * Will we need to scale the timestamps to match what the
	 * user wants?
	 */
	switch (precision) {

	case PCAP_TSTAMP_PRECISION_MICRO:
		if (magic == NSEC_TCPDUMP_MAGIC) {
			/*
			 * The file has nanoseconds, the user
			 * wants microseconds; scale the
			 * precision down.
			 */
			ps->scale_type = SCALE_DOWN;
		} else {
			/*
			 * The file has microseconds, the
			 * user wants microseconds; nothing to do.
			 */
			ps->scale_type = PASS_THROUGH;
		}
		break;

	case PCAP_TSTAMP_PRECISION_NANO:
		if (magic == NSEC_TCPDUMP_MAGIC) {
			/*
			 * The file has nanoseconds, the
			 * user wants nanoseconds; nothing to do.
			 */
			ps->scale_type = PASS_THROUGH;
		} else {
			/*
			 * The file has microoseconds, the user
			 * wants nanoseconds; scale the
			 * precision up.
			 */
			ps->scale_type = SCALE_UP;
		}
		break;

	default:
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "unknown time stamp resolution %u", precision);
		free(p);
		*err = 1;
		return (NULL);
	}

	/*
	 * We interchanged the caplen and len fields at version 2.3,
	 * in order to match the bpf header layout.  But unfortunately
	 * some files were written with version 2.3 in their headers
	 * but without the interchanged fields.
	 *
	 * In addition, DG/UX tcpdump writes out files with a version
	 * number of 543.0, and with the caplen and len fields in the
	 * pre-2.3 order.
	 */
	switch (hdr.version_major) {

	case 2:
		if (hdr.version_minor < 3)
			ps->lengths_swapped = SWAPPED;
		else if (hdr.version_minor == 3)
			ps->lengths_swapped = MAYBE_SWAPPED;
		else
			ps->lengths_swapped = NOT_SWAPPED;
		break;

	case 543:
		ps->lengths_swapped = SWAPPED;
		break;

	default:
		ps->lengths_swapped = NOT_SWAPPED;
		break;
	}

	if (magic == KUZNETZOV_TCPDUMP_MAGIC) {
		/*
		 * XXX - the patch that's in some versions of libpcap
		 * changes the packet header but not the magic number,
		 * and some other versions with this magic number have
		 * some extra debugging information in the packet header;
		 * we'd have to use some hacks^H^H^H^H^Hheuristics to
		 * detect those variants.
		 *
		 * Ethereal does that, but it does so by trying to read
		 * the first two packets of the file with each of the
		 * record header formats.  That currently means it seeks
		 * backwards and retries the reads, which doesn't work
		 * on pipes.  We want to be able to read from a pipe, so
		 * that strategy won't work; we'd have to buffer some
		 * data ourselves and read from that buffer in order to
		 * make that work.
		 */
		ps->hdrsize = sizeof(struct pcap_sf_patched_pkthdr);

		if (p->linktype == DLT_EN10MB) {
			/*
			 * This capture might have been done in raw mode
			 * or cooked mode.
			 *
			 * If it was done in cooked mode, p->snapshot was
			 * passed to recvfrom() as the buffer size, meaning
			 * that the most packet data that would be copied
			 * would be p->snapshot.  However, a faked Ethernet
			 * header would then have been added to it, so the
			 * most data that would be in a packet in the file
			 * would be p->snapshot + 14.
			 *
			 * We can't easily tell whether the capture was done
			 * in raw mode or cooked mode, so we'll assume it was
			 * cooked mode, and add 14 to the snapshot length.
			 * That means that, for a raw capture, the snapshot
			 * length will be misleading if you use it to figure
			 * out why a capture doesn't have all the packet data,
			 * but there's not much we can do to avoid that.
			 */
			p->snapshot += 14;
		}
	} else
		ps->hdrsize = sizeof(struct pcap_sf_pkthdr);

	/*
	 * Allocate a buffer for the packet data.
	 * Choose the minimum of the file's snapshot length and 2K bytes;
	 * that should be enough for most network packets - we'll grow it
	 * if necessary.  That way, we don't allocate a huge chunk of
	 * memory just because there's a huge snapshot length, as the
	 * snapshot length might be larger than the size of the largest
	 * packet.
	 */
	p->bufsize = p->snapshot;
	if (p->bufsize > 2048)
		p->bufsize = 2048;
	p->buffer = malloc(p->bufsize);
	if (p->buffer == NULL) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "out of memory");
		free(p);
		*err = 1;
		return (NULL);
	}

	p->cleanup_op = sf_cleanup;

	return (p);
}