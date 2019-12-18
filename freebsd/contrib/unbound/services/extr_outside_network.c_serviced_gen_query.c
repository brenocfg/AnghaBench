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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
serviced_gen_query(sldns_buffer* buff, uint8_t* qname, size_t qnamelen, 
	uint16_t qtype, uint16_t qclass, uint16_t flags)
{
	sldns_buffer_clear(buff);
	/* skip id */
	sldns_buffer_write_u16(buff, flags);
	sldns_buffer_write_u16(buff, 1); /* qdcount */
	sldns_buffer_write_u16(buff, 0); /* ancount */
	sldns_buffer_write_u16(buff, 0); /* nscount */
	sldns_buffer_write_u16(buff, 0); /* arcount */
	sldns_buffer_write(buff, qname, qnamelen);
	sldns_buffer_write_u16(buff, qtype);
	sldns_buffer_write_u16(buff, qclass);
	sldns_buffer_flip(buff);
}