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
typedef  int /*<<< orphan*/  ldns_buffer ;
typedef  int /*<<< orphan*/  DSA ;

/* Variables and functions */
 scalar_t__ ldns_buffer_begin (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_buffer_position (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_key_buf2dsa_raw (unsigned char const*,int /*<<< orphan*/ ) ; 

DSA *
ldns_key_buf2dsa(const ldns_buffer *key)
{
	return ldns_key_buf2dsa_raw((const unsigned char*)ldns_buffer_begin(key),
						   ldns_buffer_position(key));
}