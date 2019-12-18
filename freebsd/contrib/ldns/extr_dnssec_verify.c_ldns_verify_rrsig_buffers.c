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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__ ldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_buffers_raw (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ldns_status
ldns_verify_rrsig_buffers(ldns_buffer *rawsig_buf, ldns_buffer *verify_buf, 
					 ldns_buffer *key_buf, uint8_t algo)
{
	return ldns_verify_rrsig_buffers_raw(
			 (unsigned char*)ldns_buffer_begin(rawsig_buf),
			 ldns_buffer_position(rawsig_buf),
			 verify_buf,
			 (unsigned char*)ldns_buffer_begin(key_buf), 
			 ldns_buffer_position(key_buf), algo);
}