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
typedef  int /*<<< orphan*/  prefix ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*,size_t,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,size_t) ; 

void __dump_byte_array(const char *name, const u8 *buf, size_t len)
{
	char prefix[64];

	if (!buf)
		return;

	snprintf(prefix, sizeof(prefix), "%s[%zu]: ", name, len);

	print_hex_dump(KERN_DEBUG, prefix, DUMP_PREFIX_ADDRESS, 16, 1, buf,
		       len, false);
}