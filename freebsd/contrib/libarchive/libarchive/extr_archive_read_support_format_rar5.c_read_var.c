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
typedef  size_t uint8_t ;
typedef  size_t uint64_t ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ consume (struct archive_read*,int) ; 
 int /*<<< orphan*/  read_ahead (struct archive_read*,int,size_t const**) ; 

__attribute__((used)) static int read_var(struct archive_read* a, uint64_t* pvalue,
    uint64_t* pvalue_len)
{
	uint64_t result = 0;
	size_t shift, i;
	const uint8_t* p;
	uint8_t b;

	/* We will read maximum of 8 bytes. We don't have to handle the
	 * situation to read the RAR5 variable-sized value stored at the end of
	 * the file, because such situation will never happen. */
	if(!read_ahead(a, 8, &p))
		return 0;

	for(shift = 0, i = 0; i < 8; i++, shift += 7) {
		b = p[i];

		/* Strip the MSB from the input byte and add the resulting
		 * number to the `result`. */
		result += (b & (uint64_t)0x7F) << shift;

		/* MSB set to 1 means we need to continue decoding process.
		 * MSB set to 0 means we're done.
		 *
		 * This conditional checks for the second case. */
		if((b & 0x80) == 0) {
			if(pvalue) {
				*pvalue = result;
			}

			/* If the caller has passed the `pvalue_len` pointer,
			 * store the number of consumed bytes in it and do NOT
			 * consume those bytes, since the caller has all the
			 * information it needs to perform */
			if(pvalue_len) {
				*pvalue_len = 1 + i;
			} else {
				/* If the caller did not provide the
				 * `pvalue_len` pointer, it will not have the
				 * possibility to advance the file pointer,
				 * because it will not know how many bytes it
				 * needs to consume. This is why we handle
				 * such situation here automatically. */
				if(ARCHIVE_OK != consume(a, 1 + i)) {
					return 0;
				}
			}

			/* End of decoding process, return success. */
			return 1;
		}
	}

	/* The decoded value takes the maximum number of 8 bytes.
	 * It's a maximum number of bytes, so end decoding process here
	 * even if the first bit of last byte is 1. */
	if(pvalue) {
		*pvalue = result;
	}

	if(pvalue_len) {
		*pvalue_len = 9;
	} else {
		if(ARCHIVE_OK != consume(a, 9)) {
			return 0;
		}
	}

	return 1;
}