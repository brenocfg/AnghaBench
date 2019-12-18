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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND16 (int const) ; 
 scalar_t__ dnsname_to_labels (int /*<<< orphan*/ * const,size_t,scalar_t__,char const* const,size_t const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evdns_request_data_build(const char *const name, const size_t name_len,
    const u16 trans_id, const u16 type, const u16 class,
    u8 *const buf, size_t buf_len) {
	off_t j = 0;  /* current offset into buf */
	u16 t_;	 /* used by the macros */

	APPEND16(trans_id);
	APPEND16(0x0100);  /* standard query, recusion needed */
	APPEND16(1);  /* one question */
	APPEND16(0);  /* no answers */
	APPEND16(0);  /* no authority */
	APPEND16(0);  /* no additional */

	j = dnsname_to_labels(buf, buf_len, j, name, name_len, NULL);
	if (j < 0) {
		return (int)j;
	}

	APPEND16(type);
	APPEND16(class);

	return (int)j;
 overflow:
	return (-1);
}