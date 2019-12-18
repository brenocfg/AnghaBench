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
typedef  size_t uint16_t ;
struct regional {int dummy; } ;
struct edns_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  edns_opt_append (struct edns_data*,struct regional*,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 size_t sldns_read_uint16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parse_edns_options(uint8_t* rdata_ptr, size_t rdata_len,
	struct edns_data* edns, struct regional* region)
{
	/* while still more options, and have code+len to read */
	/* ignores partial content (i.e. rdata len 3) */
	while(rdata_len >= 4) {
		uint16_t opt_code = sldns_read_uint16(rdata_ptr);
		uint16_t opt_len = sldns_read_uint16(rdata_ptr+2);
		rdata_ptr += 4;
		rdata_len -= 4;
		if(opt_len > rdata_len)
			break; /* option code partial */
		if(!edns_opt_append(edns, region, opt_code, opt_len,
			rdata_ptr)) {
			log_err("out of memory");
			return 0;
		}
		rdata_ptr += opt_len;
		rdata_len -= opt_len;
	}
	return 1;
}