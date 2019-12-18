#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
struct sldns_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {scalar_t__ _dname_count; int* _wireformat; } ;
typedef  TYPE_1__ sldns_rr_descriptor ;
typedef  struct sldns_buffer sldns_buffer ;

/* Variables and functions */
#define  LDNS_RDF_TYPE_DNAME 129 
#define  LDNS_RDF_TYPE_STR 128 
 int /*<<< orphan*/  dname_pkt_copy (struct sldns_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t get_rdf_size (int) ; 
 size_t pkt_dname_len (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_available (struct sldns_buffer*,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_begin (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_clear (struct sldns_buffer*) ; 
 int /*<<< orphan*/ * sldns_buffer_current (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_flip (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_init_frm_data (struct sldns_buffer*,int /*<<< orphan*/ *,size_t) ; 
 size_t sldns_buffer_position (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (struct sldns_buffer*,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_skip (struct sldns_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write (struct sldns_buffer*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (struct sldns_buffer*,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16_at (struct sldns_buffer*,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u32 (struct sldns_buffer*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sldns_rr_descript (size_t) ; 

__attribute__((used)) static int
decompress_rr_into_buffer(struct sldns_buffer* buf, uint8_t* pkt,
	size_t pktlen, uint8_t* dname, uint16_t rr_type, uint16_t rr_class,
	uint32_t rr_ttl, uint8_t* rr_data, uint16_t rr_rdlen)
{
	sldns_buffer pktbuf;
	size_t dname_len = 0;
	size_t rdlenpos;
	size_t rdlen;
	uint8_t* rd;
	const sldns_rr_descriptor* desc;
	sldns_buffer_init_frm_data(&pktbuf, pkt, pktlen);
	sldns_buffer_clear(buf);

	/* decompress dname */
	sldns_buffer_set_position(&pktbuf,
		(size_t)(dname - sldns_buffer_current(&pktbuf)));
	dname_len = pkt_dname_len(&pktbuf);
	if(dname_len == 0) return 0; /* parse fail on dname */
	if(!sldns_buffer_available(buf, dname_len)) return 0;
	dname_pkt_copy(&pktbuf, sldns_buffer_current(buf), dname);
	sldns_buffer_skip(buf, (ssize_t)dname_len);

	/* type, class, ttl and rdatalength fields */
	if(!sldns_buffer_available(buf, 10)) return 0;
	sldns_buffer_write_u16(buf, rr_type);
	sldns_buffer_write_u16(buf, rr_class);
	sldns_buffer_write_u32(buf, rr_ttl);
	rdlenpos = sldns_buffer_position(buf);
	sldns_buffer_write_u16(buf, 0); /* rd length position */

	/* decompress rdata */
	desc = sldns_rr_descript(rr_type);
	rd = rr_data;
	rdlen = rr_rdlen;
	if(rdlen > 0 && desc && desc->_dname_count > 0) {
		int count = (int)desc->_dname_count;
		int rdf = 0;
		size_t len; /* how much rdata to plain copy */
		size_t uncompressed_len, compressed_len;
		size_t oldpos;
		/* decompress dnames. */
		while(rdlen > 0 && count) {
			switch(desc->_wireformat[rdf]) {
			case LDNS_RDF_TYPE_DNAME:
				sldns_buffer_set_position(&pktbuf,
					(size_t)(rd -
					sldns_buffer_begin(&pktbuf)));
				oldpos = sldns_buffer_position(&pktbuf);
				/* moves pktbuf to right after the
				 * compressed dname, and returns uncompressed
				 * dname length */
				uncompressed_len = pkt_dname_len(&pktbuf);
				if(!uncompressed_len)
					return 0; /* parse error in dname */
				if(!sldns_buffer_available(buf,
					uncompressed_len))
					/* dname too long for buffer */
					return 0;
				dname_pkt_copy(&pktbuf, 
					sldns_buffer_current(buf), rd);
				sldns_buffer_skip(buf, (ssize_t)uncompressed_len);
				compressed_len = sldns_buffer_position(
					&pktbuf) - oldpos;
				rd += compressed_len;
				rdlen -= compressed_len;
				count--;
				len = 0;
				break;
			case LDNS_RDF_TYPE_STR:
				len = rd[0] + 1;
				break;
			default:
				len = get_rdf_size(desc->_wireformat[rdf]);
				break;
			}
			if(len) {
				if(!sldns_buffer_available(buf, len))
					return 0; /* too long for buffer */
				sldns_buffer_write(buf, rd, len);
				rd += len;
				rdlen -= len;
			}
			rdf++;
		}
	}
	/* copy remaining data */
	if(rdlen > 0) {
		if(!sldns_buffer_available(buf, rdlen)) return 0;
		sldns_buffer_write(buf, rd, rdlen);
	}
	/* fixup rdlength */
	sldns_buffer_write_u16_at(buf, rdlenpos,
		sldns_buffer_position(buf)-rdlenpos-2);
	sldns_buffer_flip(buf);
	return 1;
}