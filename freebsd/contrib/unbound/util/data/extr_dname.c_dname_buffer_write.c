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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 size_t sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,scalar_t__) ; 

int 
dname_buffer_write(sldns_buffer* pkt, uint8_t* dname)
{
	uint8_t lablen;

	if(sldns_buffer_remaining(pkt) < 1)
		return 0;
	lablen = *dname++;
	sldns_buffer_write_u8(pkt, lablen);
	while(lablen) {
		if(sldns_buffer_remaining(pkt) < (size_t)lablen+1)
			return 0;
		sldns_buffer_write(pkt, dname, lablen);
		dname += lablen;
		lablen = *dname++;
		sldns_buffer_write_u8(pkt, lablen);
	}
	return 1;
}