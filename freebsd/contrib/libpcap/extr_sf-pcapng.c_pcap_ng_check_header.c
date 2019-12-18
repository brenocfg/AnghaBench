#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  total_length ;
struct section_header_block {void* minor_version; void* major_version; scalar_t__ byte_order_magic; } ;
struct pcap_ng_sf {int user_tsresol; scalar_t__ max_blocksize; TYPE_2__* ifaces; } ;
struct interface_description_block {scalar_t__ snaplen; void* linktype; } ;
struct block_trailer {int dummy; } ;
struct block_header {scalar_t__ total_length; scalar_t__ block_type; } ;
struct block_cursor {int block_type; } ;
struct TYPE_9__ {int tstamp_precision; } ;
struct TYPE_10__ {int swapped; int bufsize; scalar_t__ snapshot; struct TYPE_10__* buffer; int /*<<< orphan*/  cleanup_op; int /*<<< orphan*/  next_packet_op; void* linktype; scalar_t__ linktype_ext; scalar_t__ tzoff; TYPE_1__ opt; void* version_minor; void* version_major; struct pcap_ng_sf* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  byte_order_magic ;
typedef  scalar_t__ bpf_u_int32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  BT_EPB 133 
#define  BT_IDB 132 
#define  BT_PB 131 
 scalar_t__ BT_SHB ; 
#define  BT_SPB 130 
 scalar_t__ BYTE_ORDER_MAGIC ; 
 scalar_t__ MAXIMUM_SNAPLEN ; 
 scalar_t__ MAX_BLOCKSIZE (scalar_t__) ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 void* PCAP_NG_VERSION_MAJOR ; 
 void* PCAP_NG_VERSION_MINOR ; 
#define  PCAP_TSTAMP_PRECISION_MICRO 129 
#define  PCAP_TSTAMP_PRECISION_NANO 128 
 scalar_t__ SWAPLONG (scalar_t__) ; 
 void* SWAPSHORT (void*) ; 
 int /*<<< orphan*/  add_interface (TYPE_2__*,struct block_cursor*,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 struct interface_description_block* get_from_block_data (struct block_cursor*,int,char*) ; 
 void* linktype_to_dlt (void*) ; 
 TYPE_2__* malloc (scalar_t__) ; 
 scalar_t__ max_snaplen_for_dlt (void*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_ng_cleanup ; 
 int /*<<< orphan*/  pcap_ng_next_packet ; 
 TYPE_2__* pcap_open_offline_common (char*,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int read_block (int /*<<< orphan*/ *,TYPE_2__*,struct block_cursor*,char*) ; 
 int read_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,char*) ; 

pcap_t *
pcap_ng_check_header(bpf_u_int32 magic, FILE *fp, u_int precision, char *errbuf,
    int *err)
{
	size_t amt_read;
	bpf_u_int32 total_length;
	bpf_u_int32 byte_order_magic;
	struct block_header *bhdrp;
	struct section_header_block *shbp;
	pcap_t *p;
	int swapped = 0;
	struct pcap_ng_sf *ps;
	int status;
	struct block_cursor cursor;
	struct interface_description_block *idbp;

	/*
	 * Assume no read errors.
	 */
	*err = 0;

	/*
	 * Check whether the first 4 bytes of the file are the block
	 * type for a pcapng savefile.
	 */
	if (magic != BT_SHB) {
		/*
		 * XXX - check whether this looks like what the block
		 * type would be after being munged by mapping between
		 * UN*X and DOS/Windows text file format and, if it
		 * does, look for the byte-order magic number in
		 * the appropriate place and, if we find it, report
		 * this as possibly being a pcapng file transferred
		 * between UN*X and Windows in text file format?
		 */
		return (NULL);	/* nope */
	}

	/*
	 * OK, they are.  However, that's just \n\r\r\n, so it could,
	 * conceivably, be an ordinary text file.
	 *
	 * It could not, however, conceivably be any other type of
	 * capture file, so we can read the rest of the putative
	 * Section Header Block; put the block type in the common
	 * header, read the rest of the common header and the
	 * fixed-length portion of the SHB, and look for the byte-order
	 * magic value.
	 */
	amt_read = fread(&total_length, 1, sizeof(total_length), fp);
	if (amt_read < sizeof(total_length)) {
		if (ferror(fp)) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "error reading dump file");
			*err = 1;
			return (NULL);	/* fail */
		}

		/*
		 * Possibly a weird short text file, so just say
		 * "not pcapng".
		 */
		return (NULL);
	}
	amt_read = fread(&byte_order_magic, 1, sizeof(byte_order_magic), fp);
	if (amt_read < sizeof(byte_order_magic)) {
		if (ferror(fp)) {
			pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
			    errno, "error reading dump file");
			*err = 1;
			return (NULL);	/* fail */
		}

		/*
		 * Possibly a weird short text file, so just say
		 * "not pcapng".
		 */
		return (NULL);
	}
	if (byte_order_magic != BYTE_ORDER_MAGIC) {
		byte_order_magic = SWAPLONG(byte_order_magic);
		if (byte_order_magic != BYTE_ORDER_MAGIC) {
			/*
			 * Not a pcapng file.
			 */
			return (NULL);
		}
		swapped = 1;
		total_length = SWAPLONG(total_length);
	}

	/*
	 * Check the sanity of the total length.
	 */
	if (total_length < sizeof(*bhdrp) + sizeof(*shbp) + sizeof(struct block_trailer)) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "Section Header Block in pcapng dump file has a length of %u < %lu",
		    total_length,
		    (unsigned long)(sizeof(*bhdrp) + sizeof(*shbp) + sizeof(struct block_trailer)));
		*err = 1;
		return (NULL);
	}

	/*
	 * OK, this is a good pcapng file.
	 * Allocate a pcap_t for it.
	 */
	p = pcap_open_offline_common(errbuf, sizeof (struct pcap_ng_sf));
	if (p == NULL) {
		/* Allocation failed. */
		*err = 1;
		return (NULL);
	}
	p->swapped = swapped;
	ps = p->priv;

	/*
	 * What precision does the user want?
	 */
	switch (precision) {

	case PCAP_TSTAMP_PRECISION_MICRO:
		ps->user_tsresol = 1000000;
		break;

	case PCAP_TSTAMP_PRECISION_NANO:
		ps->user_tsresol = 1000000000;
		break;

	default:
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "unknown time stamp resolution %u", precision);
		free(p);
		*err = 1;
		return (NULL);
	}

	p->opt.tstamp_precision = precision;

	/*
	 * Allocate a buffer into which to read blocks.  We default to
	 * the maximum of:
	 *
	 *	the total length of the SHB for which we read the header;
	 *
	 *	2K, which should be more than large enough for an Enhanced
	 *	Packet Block containing a full-size Ethernet frame, and
	 *	leaving room for some options.
	 *
	 * If we find a bigger block, we reallocate the buffer, up to
	 * the maximum size.  We start out with a maximum size based
	 * on a maximum snapshot length of MAXIMUM_SNAPLEN; if we see
	 * any link-layer header types with a larger maximum snapshot
	 * length, we boost the maximum.
	 */
	p->bufsize = 2048;
	if (p->bufsize < total_length)
		p->bufsize = total_length;
	p->buffer = malloc(p->bufsize);
	if (p->buffer == NULL) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "out of memory");
		free(p);
		*err = 1;
		return (NULL);
	}
	ps->max_blocksize = MAX_BLOCKSIZE(MAXIMUM_SNAPLEN);

	/*
	 * Copy the stuff we've read to the buffer, and read the rest
	 * of the SHB.
	 */
	bhdrp = (struct block_header *)p->buffer;
	shbp = (struct section_header_block *)((u_char *)p->buffer + sizeof(struct block_header));
	bhdrp->block_type = magic;
	bhdrp->total_length = total_length;
	shbp->byte_order_magic = byte_order_magic;
	if (read_bytes(fp,
	    (u_char *)p->buffer + (sizeof(magic) + sizeof(total_length) + sizeof(byte_order_magic)),
	    total_length - (sizeof(magic) + sizeof(total_length) + sizeof(byte_order_magic)),
	    1, errbuf) == -1)
		goto fail;

	if (p->swapped) {
		/*
		 * Byte-swap the fields we've read.
		 */
		shbp->major_version = SWAPSHORT(shbp->major_version);
		shbp->minor_version = SWAPSHORT(shbp->minor_version);

		/*
		 * XXX - we don't care about the section length.
		 */
	}
	/* currently only SHB version 1.0 is supported */
	if (! (shbp->major_version == PCAP_NG_VERSION_MAJOR &&
	       shbp->minor_version == PCAP_NG_VERSION_MINOR)) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "unsupported pcapng savefile version %u.%u",
		    shbp->major_version, shbp->minor_version);
		goto fail;
	}
	p->version_major = shbp->major_version;
	p->version_minor = shbp->minor_version;

	/*
	 * Save the time stamp resolution the user requested.
	 */
	p->opt.tstamp_precision = precision;

	/*
	 * Now start looking for an Interface Description Block.
	 */
	for (;;) {
		/*
		 * Read the next block.
		 */
		status = read_block(fp, p, &cursor, errbuf);
		if (status == 0) {
			/* EOF - no IDB in this file */
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "the capture file has no Interface Description Blocks");
			goto fail;
		}
		if (status == -1)
			goto fail;	/* error */
		switch (cursor.block_type) {

		case BT_IDB:
			/*
			 * Get a pointer to the fixed-length portion of the
			 * IDB.
			 */
			idbp = get_from_block_data(&cursor, sizeof(*idbp),
			    errbuf);
			if (idbp == NULL)
				goto fail;	/* error */

			/*
			 * Byte-swap it if necessary.
			 */
			if (p->swapped) {
				idbp->linktype = SWAPSHORT(idbp->linktype);
				idbp->snaplen = SWAPLONG(idbp->snaplen);
			}

			/*
			 * Try to add this interface.
			 */
			if (!add_interface(p, &cursor, errbuf))
				goto fail;

			goto done;

		case BT_EPB:
		case BT_SPB:
		case BT_PB:
			/*
			 * Saw a packet before we saw any IDBs.  That's
			 * not valid, as we don't know what link-layer
			 * encapsulation the packet has.
			 */
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "the capture file has a packet block before any Interface Description Blocks");
			goto fail;

		default:
			/*
			 * Just ignore it.
			 */
			break;
		}
	}

done:
	p->tzoff = 0;	/* XXX - not used in pcap */
	p->snapshot = idbp->snaplen;
	if (p->snapshot <= 0) {
		/*
		 * Bogus snapshot length; use the maximum for this
		 * link-layer type as a fallback.
		 *
		 * XXX - the only reason why snapshot is signed is
		 * that pcap_snapshot() returns an int, not an
		 * unsigned int.
		 */
		p->snapshot = max_snaplen_for_dlt(idbp->linktype);
	}
	p->linktype = linktype_to_dlt(idbp->linktype);
	p->linktype_ext = 0;

	/*
	 * If the maximum block size for a packet with the maximum
	 * snapshot length for this DLT_ is bigger than the current
	 * maximum block size, increase the maximum.
	 */
	if (MAX_BLOCKSIZE(max_snaplen_for_dlt(p->linktype)) > ps->max_blocksize)
		ps->max_blocksize = MAX_BLOCKSIZE(max_snaplen_for_dlt(p->linktype));

	p->next_packet_op = pcap_ng_next_packet;
	p->cleanup_op = pcap_ng_cleanup;

	return (p);

fail:
	free(ps->ifaces);
	free(p->buffer);
	free(p);
	*err = 1;
	return (NULL);
}