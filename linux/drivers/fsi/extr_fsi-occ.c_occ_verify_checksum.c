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
typedef  size_t u16 ;
struct occ_response {size_t* data; size_t seq_no; size_t cmd_type; size_t return_status; } ;

/* Variables and functions */
 int EBADMSG ; 
 size_t get_unaligned_be16 (size_t*) ; 

__attribute__((used)) static int occ_verify_checksum(struct occ_response *resp, u16 data_length)
{
	/* Fetch the two bytes after the data for the checksum. */
	u16 checksum_resp = get_unaligned_be16(&resp->data[data_length]);
	u16 checksum;
	u16 i;

	checksum = resp->seq_no;
	checksum += resp->cmd_type;
	checksum += resp->return_status;
	checksum += (data_length >> 8) + (data_length & 0xFF);

	for (i = 0; i < data_length; ++i)
		checksum += resp->data[i];

	if (checksum != checksum_resp)
		return -EBADMSG;

	return 0;
}