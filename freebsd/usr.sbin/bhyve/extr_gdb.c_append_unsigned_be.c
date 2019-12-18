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
typedef  int uintmax_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  append_packet_data (char*,int) ; 
 int /*<<< orphan*/  format_byte (int,char*) ; 

__attribute__((used)) static void
append_unsigned_be(uintmax_t value, size_t len)
{
	char buf[len * 2];
	size_t i;

	for (i = 0; i < len; i++) {
		format_byte(value, buf + (len - i - 1) * 2);
		value >>= 8;
	}
	append_packet_data(buf, sizeof(buf));
}