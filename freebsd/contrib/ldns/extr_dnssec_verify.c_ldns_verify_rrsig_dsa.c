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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__ ldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_dsa_raw (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

ldns_status
ldns_verify_rrsig_dsa(ldns_buffer *sig, ldns_buffer *rrset, ldns_buffer *key)
{
	return ldns_verify_rrsig_dsa_raw(
			 (unsigned char*) ldns_buffer_begin(sig),
			 ldns_buffer_position(sig),
			 rrset,
			 (unsigned char*) ldns_buffer_begin(key),
			 ldns_buffer_position(key));
}