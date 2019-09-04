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
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  unpack_object_header_buffer (unsigned char const*,unsigned long,int*,unsigned long*) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	enum object_type type;
	unsigned long len;

	unpack_object_header_buffer((const unsigned char *)data,
				    (unsigned long)size, &type, &len);

	return 0;
}