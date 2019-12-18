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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct rar5 {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ read_bits_16 (struct rar5*,int /*<<< orphan*/  const*,scalar_t__*) ; 
 scalar_t__ read_consume_bits (struct rar5*,int /*<<< orphan*/  const*,int,int*) ; 
 int /*<<< orphan*/  skip_bits (struct rar5*,int) ; 

__attribute__((used)) static int parse_filter_data(struct rar5* rar, const uint8_t* p,
    uint32_t* filter_data)
{
	int i, bytes;
	uint32_t data = 0;

	if(ARCHIVE_OK != read_consume_bits(rar, p, 2, &bytes))
		return ARCHIVE_EOF;

	bytes++;

	for(i = 0; i < bytes; i++) {
		uint16_t byte;

		if(ARCHIVE_OK != read_bits_16(rar, p, &byte)) {
			return ARCHIVE_EOF;
		}

		/* Cast to uint32_t will ensure the shift operation will not
		 * produce undefined result. */
		data += ((uint32_t) byte >> 8) << (i * 8);
		skip_bits(rar, 8);
	}

	*filter_data = data;
	return ARCHIVE_OK;
}