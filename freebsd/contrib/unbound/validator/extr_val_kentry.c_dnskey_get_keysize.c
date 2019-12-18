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
struct packed_rrset_data {int* rr_len; scalar_t__** rr_data; } ;

/* Variables and functions */
 size_t sldns_rr_dnskey_key_size_raw (unsigned char*,unsigned int,int) ; 

__attribute__((used)) static size_t
dnskey_get_keysize(struct packed_rrset_data* data, size_t idx)
{
	unsigned char* pk;
	unsigned int pklen = 0;
	int algo;
	if(data->rr_len[idx] < 2+5)
		return 0;
	algo = (int)data->rr_data[idx][2+3];
	pk = (unsigned char*)data->rr_data[idx]+2+4;
	pklen = (unsigned)data->rr_len[idx]-2-4;
	return sldns_rr_dnskey_key_size_raw(pk, pklen, algo);
}