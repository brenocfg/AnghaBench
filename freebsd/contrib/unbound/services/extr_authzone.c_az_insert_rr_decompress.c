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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sldns_buffer {int dummy; } ;
struct auth_zone {int dummy; } ;

/* Variables and functions */
 int az_insert_rr (struct auth_zone*,int /*<<< orphan*/ *,size_t,size_t,int*) ; 
 int /*<<< orphan*/  decompress_rr_into_buffer (struct sldns_buffer*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t dname_valid (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/ * sldns_buffer_begin (struct sldns_buffer*) ; 
 size_t sldns_buffer_limit (struct sldns_buffer*) ; 

__attribute__((used)) static int
az_insert_rr_decompress(struct auth_zone* z, uint8_t* pkt, size_t pktlen,
	struct sldns_buffer* scratch_buffer, uint8_t* dname, uint16_t rr_type,
	uint16_t rr_class, uint32_t rr_ttl, uint8_t* rr_data,
	uint16_t rr_rdlen, int* duplicate)
{
	uint8_t* rr;
	size_t rr_len;
	size_t dname_len;
	if(!decompress_rr_into_buffer(scratch_buffer, pkt, pktlen, dname,
		rr_type, rr_class, rr_ttl, rr_data, rr_rdlen)) {
		log_err("could not decompress RR");
		return 0;
	}
	rr = sldns_buffer_begin(scratch_buffer);
	rr_len = sldns_buffer_limit(scratch_buffer);
	dname_len = dname_valid(rr, rr_len);
	return az_insert_rr(z, rr, rr_len, dname_len, duplicate);
}