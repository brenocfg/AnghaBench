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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 scalar_t__ ldns_buffer_reserve (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_write (int /*<<< orphan*/ *,int*,long) ; 
 int /*<<< orphan*/  ldns_buffer_write_u8 (int /*<<< orphan*/ *,long) ; 
 int* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/  const*) ; 

ldns_status
ldns_convert_ecdsa_rrsig_rdf2asn1(ldns_buffer *target_buffer,
        const ldns_rdf *sig_rdf)
{
        /* convert from two BIGNUMs in the rdata buffer, to ASN notation.
	 * ASN preable:  30440220 <R 32bytefor256> 0220 <S 32bytefor256>
	 * the '20' is the length of that field (=bnsize).
	 * the '44' is the total remaining length.
	 * if negative, start with leading zero.
	 * if starts with 00s, remove them from the number.
	 */
        uint8_t pre[] = {0x30, 0x44, 0x02, 0x20};
        int pre_len = 4;
        uint8_t mid[] = {0x02, 0x20};
        int mid_len = 2;
        int raw_sig_len, r_high, s_high, r_rem=0, s_rem=0;
        long bnsize = (long)ldns_rdf_size(sig_rdf) / 2;
        uint8_t* d = ldns_rdf_data(sig_rdf);
        /* if too short, or not even length, do not bother */
        if(bnsize < 16 || (size_t)bnsize*2 != ldns_rdf_size(sig_rdf))
                return LDNS_STATUS_ERR;
        /* strip leading zeroes from r (but not last one) */
        while(r_rem < bnsize-1 && d[r_rem] == 0)
                r_rem++;
        /* strip leading zeroes from s (but not last one) */
        while(s_rem < bnsize-1 && d[bnsize+s_rem] == 0)
                s_rem++;

        r_high = ((d[0+r_rem]&0x80)?1:0);
        s_high = ((d[bnsize+s_rem]&0x80)?1:0);
        raw_sig_len = pre_len + r_high + bnsize - r_rem + mid_len +
		s_high + bnsize - s_rem;
        if(ldns_buffer_reserve(target_buffer, (size_t) raw_sig_len)) {
                ldns_buffer_write_u8(target_buffer, pre[0]);
                ldns_buffer_write_u8(target_buffer, raw_sig_len-2);
                ldns_buffer_write_u8(target_buffer, pre[2]);
                ldns_buffer_write_u8(target_buffer, bnsize + r_high - r_rem);
                if(r_high)
                        ldns_buffer_write_u8(target_buffer, 0);
                ldns_buffer_write(target_buffer, d+r_rem, bnsize-r_rem);
                ldns_buffer_write(target_buffer, mid, mid_len-1);
                ldns_buffer_write_u8(target_buffer, bnsize + s_high - s_rem);
                if(s_high)
                        ldns_buffer_write_u8(target_buffer, 0);
                ldns_buffer_write(target_buffer, d+bnsize+s_rem, bnsize-s_rem);
        }
        return ldns_buffer_status(target_buffer);
}