#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mpeg_pldt {int /*<<< orphan*/  payload; } ;
struct TYPE_7__ {int len; } ;
struct TYPE_8__ {TYPE_3__ stream; } ;
struct fw_pkt {TYPE_4__ mode; } ;
struct TYPE_6__ {scalar_t__ psize; scalar_t__ npacket; scalar_t__ nchunk; } ;
struct TYPE_5__ {int /*<<< orphan*/  psize; int /*<<< orphan*/  npacket; int /*<<< orphan*/  nchunk; } ;
struct fw_isochreq {char ch; char tag; TYPE_2__ tx; TYPE_1__ rx; } ;
struct fw_isobufreq {char ch; char tag; TYPE_2__ tx; TYPE_1__ rx; } ;
struct ciphdr {scalar_t__ fmt; int fn; int len; int qpc; int dbc; } ;

/* Variables and functions */
 scalar_t__ CIP_FMT_MPEG ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  FW_SRSTREAM ; 
 int /*<<< orphan*/  FW_SSTBUF ; 
 int /*<<< orphan*/  NCHUNK ; 
 int /*<<< orphan*/  NPACKET_R ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  RBUFSIZE ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct fw_isochreq*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int open (char const*,int,int) ; 
 int read (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ ,int) ; 

void
mpegtsrecv(int d, const char *filename, char ich, int count)
{
	struct ciphdr *ciph;
	struct fw_isochreq isoreq;
	struct fw_isobufreq bufreq;
	struct fw_pkt *pkt;
	struct mpeg_pldt *pld;
	uint32_t *ptr;
	int fd, k, len, m, pkt_size, startwr, tlen;
	char *buf;

	startwr = 0;

	if (strcmp(filename, "-") == 0)
		fd = STDOUT_FILENO;
	else {
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0660);
		if (fd == -1)
			err(EX_NOINPUT, "%s", filename);
	}
	buf = malloc(RBUFSIZE);

	bufreq.rx.nchunk = NCHUNK;
	bufreq.rx.npacket = NPACKET_R;
	bufreq.rx.psize = PSIZE;
	bufreq.tx.nchunk = 0;
	bufreq.tx.npacket = 0;
	bufreq.tx.psize = 0;
	if (ioctl(d, FW_SSTBUF, &bufreq) < 0)
		err(1, "ioctl");

	isoreq.ch = ich & 0x3f;
	isoreq.tag = (ich >> 6) & 3;

	if (ioctl(d, FW_SRSTREAM, &isoreq) < 0)
		err(1, "ioctl");

	k = m = 0;
	while (count <= 0 || k <= count) {
		len = tlen = read(d, buf, RBUFSIZE);
#if DEBUG
		fprintf(stderr, "Read %d bytes.\n", len);
#endif /* DEBUG */
		if (len < 0) {
			if (errno == EAGAIN) {
				fprintf(stderr, "(EAGAIN) - push 'Play'?\n");
				continue;
			}
			err(1, "read failed");
		}
		ptr = (uint32_t *) buf;

		do {
			pkt = (struct fw_pkt *) ptr;	
#if DEBUG
			fprintf(stderr, "\nReading new packet.\n");
			fprintf(stderr, "%08x %08x %08x %08x\n",
				htonl(ptr[0]), htonl(ptr[1]),
				htonl(ptr[2]), htonl(ptr[3]));
#endif /* DEBUG */
			/* there is no CRC in the 1394 header */
			ciph = (struct ciphdr *)(ptr + 1);	/* skip iso header */
			if (ciph->fmt != CIP_FMT_MPEG)
				errx(1, "unknown format 0x%x", ciph->fmt);
			if (ciph->fn != 3) {
				errx(1,
						"unsupported MPEG TS stream, fn=%d (only fn=3 is supported)",
						ciph->fn);
			}
			ptr = (uint32_t *) (ciph + 1);		/* skip cip header */

			if (pkt->mode.stream.len <= sizeof(struct ciphdr)) {
				/* no payload */
				/* tlen needs to be decremented before end of the loop */
				goto next;
			}
#if DEBUG
			else {
				fprintf(stderr,
						"Packet net payload length (IEEE1394 header): %d\n",
						pkt->mode.stream.len - sizeof(struct ciphdr));
				fprintf(stderr, "Data block size (CIP header): %d [q], %d [B]\n",
						ciph->len, ciph->len * 4);
				fprintf(stderr,
						"Data fraction number (CIP header): %d => DBC increments with %d\n",
						ciph->fn, (1<<ciph->fn) );
				fprintf(stderr, "QCP (CIP header): %d\n", ciph->qpc );
				fprintf(stderr, "DBC counter (CIP header): %d\n", ciph->dbc );
				fprintf(stderr, "MPEG payload type size: %d\n",
						sizeof(struct mpeg_pldt));
			}
#endif /* DEBUG */

			/* This is a condition that needs to be satisfied to start
			   writing the data */
			if (ciph->dbc % (1<<ciph->fn) == 0)
				startwr = 1;
			/* Read out all the MPEG TS data blocks from current packet */
			for (pld = (struct mpeg_pldt *)ptr;
			    (intptr_t)pld < (intptr_t)((char *)ptr +
			    pkt->mode.stream.len - sizeof(struct ciphdr));
			    pld++) {
				if (startwr == 1)
					write(fd, pld->payload,
					    sizeof(pld->payload));
			}

next:
			/* CRCs are removed from both header and trailer
			so that only 4 bytes of 1394 header remains */
			pkt_size = pkt->mode.stream.len + 4; 
			ptr = (uint32_t *)((intptr_t)pkt + pkt_size);
			tlen -= pkt_size;
		} while (tlen > 0);
#if DEBUG
		fprintf(stderr, "\nReading a data from firewire.\n");
#endif /* DEBUG */

	}
	if (fd != STDOUT_FILENO)
		close(fd);
	fprintf(stderr, "\n");
}