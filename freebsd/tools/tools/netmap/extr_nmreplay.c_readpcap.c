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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int u_long ;
struct q_pkt {int dummy; } ;
struct pcap_file_header {int dummy; } ;
struct nm_pcap_file {scalar_t__ fd; int filesize; scalar_t__ data; scalar_t__ cur; scalar_t__ lim; scalar_t__ err; int swap; int resolution; scalar_t__ tot_pkt; scalar_t__ first_ts; int tot_bytes; int total_tx_time; int /*<<< orphan*/  tot_bytes_rounded; } ;

/* Variables and functions */
 int /*<<< orphan*/  ED (char*,int,...) ; 
 int /*<<< orphan*/  EEE (char*,...) ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int NS_SCALE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  WWW (char*,int) ; 
 int /*<<< orphan*/  bzero (struct nm_pcap_file*,int) ; 
 struct nm_pcap_file* calloc (int,int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int lseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pad (int) ; 
 int read_next_info (struct nm_pcap_file*,int) ; 

__attribute__((used)) static struct nm_pcap_file *
readpcap(const char *fn)
{
    struct nm_pcap_file _f, *pf = &_f;
    uint64_t prev_ts, first_pkt_time;
    uint32_t magic, first_len = 0;

    bzero(pf, sizeof(*pf));
    pf->fd = open(fn, O_RDONLY);
    if (pf->fd < 0) {
	EEE("cannot open file %s", fn);
	return NULL;
    }
    /* compute length */
    pf->filesize = lseek(pf->fd, 0, SEEK_END);
    lseek(pf->fd, 0, SEEK_SET);
    ED("filesize is %lu", (u_long)(pf->filesize));
    if (pf->filesize < sizeof(struct pcap_file_header)) {
	EEE("file too short %s", fn);
	close(pf->fd);
	return NULL;
    }
    pf->data = mmap(NULL, pf->filesize, PROT_READ, MAP_SHARED, pf->fd, 0);
    if (pf->data == MAP_FAILED) {
	EEE("cannot mmap file %s", fn);
	close(pf->fd);
	return NULL;
    }
    pf->cur = pf->data;
    pf->lim = pf->data + pf->filesize;
    pf->err = 0;
    pf->swap = 0; /* default, same endianness when read magic */

    magic = read_next_info(pf, 4);
    ED("magic is 0x%x", magic);
    switch (magic) {
    case 0xa1b2c3d4: /* native, us resolution */
	pf->swap = 0;
	pf->resolution = 1000;
	break;
    case 0xd4c3b2a1: /* swapped, us resolution */
	pf->swap = 1;
	pf->resolution = 1000;
	break;
    case 0xa1b23c4d:	/* native, ns resolution */
	pf->swap = 0;
	pf->resolution = 1; /* nanoseconds */
	break;
    case 0x4d3cb2a1:	/* swapped, ns resolution */
	pf->swap = 1;
	pf->resolution = 1; /* nanoseconds */
	break;
    default:
	EEE("unknown magic 0x%x", magic);
	return NULL;
    }

    ED("swap %d res %d\n", pf->swap, pf->resolution);
    pf->cur = pf->data + sizeof(struct pcap_file_header);
    pf->lim = pf->data + pf->filesize;
    pf->err = 0;
    prev_ts = 0;
    while (pf->cur < pf->lim && pf->err == 0) {
	uint32_t base = pf->cur - pf->data;
	uint64_t cur_ts = read_next_info(pf, 4) * NS_SCALE +
		read_next_info(pf, 4) * pf->resolution;
	uint32_t caplen = read_next_info(pf, 4);
	uint32_t len = read_next_info(pf, 4);

	if (pf->err) {
	    WWW("end of pcap file after %d packets\n",
		(int)pf->tot_pkt);
	    break;
	}
	if  (cur_ts < prev_ts) {
	    WWW("reordered packet %d\n",
		(int)pf->tot_pkt);
	}
	prev_ts = cur_ts;
	(void)base;
	if (pf->tot_pkt == 0) {
	    pf->first_ts = cur_ts;
	    first_len = len;
	}
	pf->tot_pkt++;
	pf->tot_bytes += len;
	pf->tot_bytes_rounded += pad(len) + sizeof(struct q_pkt);
	pf->cur += caplen;
    }
    pf->total_tx_time = prev_ts - pf->first_ts; /* excluding first packet */
    ED("tot_pkt %lu tot_bytes %lu tx_time %.6f s first_len %lu",
	(u_long)pf->tot_pkt, (u_long)pf->tot_bytes,
	1e-9*pf->total_tx_time, (u_long)first_len);
    /*
     * We determine that based on the
     * average bandwidth of the trace, as follows
     *   first_pkt_ts = p[0].len / avg_bw
     * In turn avg_bw = (total_len - p[0].len)/(p[n-1].ts - p[0].ts)
     * so
     *   first_ts =  p[0].ts - p[0].len * (p[n-1].ts - p[0].ts) / (total_len - p[0].len)
     */
    if (pf->tot_bytes == first_len) {
	/* cannot estimate bandwidth, so force 1 Gbit */
	first_pkt_time = first_len * 8; /* * 10^9 / bw */
    } else {
	first_pkt_time = pf->total_tx_time * first_len / (pf->tot_bytes - first_len);
    }
    ED("first_pkt_time %.6f s", 1e-9*first_pkt_time);
    pf->total_tx_time += first_pkt_time;
    pf->first_ts -= first_pkt_time;

    /* all correct, allocate a record and copy */
    pf = calloc(1, sizeof(*pf));
    *pf = _f;
    /* reset pointer to start */
    pf->cur = pf->data + sizeof(struct pcap_file_header);
    pf->err = 0;
    return pf;
}