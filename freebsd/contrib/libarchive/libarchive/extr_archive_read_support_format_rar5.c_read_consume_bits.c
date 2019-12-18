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
typedef  scalar_t__ uint16_t ;
struct rar5 {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int read_bits_16 (struct rar5*,int /*<<< orphan*/  const*,scalar_t__*) ; 
 int /*<<< orphan*/  skip_bits (struct rar5*,int) ; 

__attribute__((used)) static int read_consume_bits(struct rar5* rar, const uint8_t* p, int n,
    int* value)
{
	uint16_t v;
	int ret, num;

	if(n == 0 || n > 16) {
		/* This is a programmer error and should never happen
		 * in runtime. */
		return ARCHIVE_FATAL;
	}

	ret = read_bits_16(rar, p, &v);
	if(ret != ARCHIVE_OK)
		return ret;

	num = (int) v;
	num >>= 16 - n;

	skip_bits(rar, n);

	if(value)
		*value = num;

	return ARCHIVE_OK;
}