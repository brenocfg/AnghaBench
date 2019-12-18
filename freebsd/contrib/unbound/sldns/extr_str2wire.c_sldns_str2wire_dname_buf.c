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

/* Variables and functions */
 int sldns_str2wire_dname_buf_rel (char const*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 

int sldns_str2wire_dname_buf(const char* str, uint8_t* buf, size_t* len)
{
	return sldns_str2wire_dname_buf_rel(str, buf, len, NULL);
}