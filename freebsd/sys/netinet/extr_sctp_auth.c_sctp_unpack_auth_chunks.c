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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  sctp_auth_chklist_t ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_auth_add_chunk (int,int /*<<< orphan*/ *) ; 

int
sctp_unpack_auth_chunks(const uint8_t *ptr, uint8_t num_chunks,
    sctp_auth_chklist_t *list)
{
	int i;
	int size;

	if (list == NULL)
		return (0);

	if (num_chunks <= 32) {
		/* just pull them, one byte each */
		for (i = 0; i < num_chunks; i++) {
			(void)sctp_auth_add_chunk(*ptr++, list);
		}
		size = num_chunks;
	} else {
		int index, offset;

		/* unpack from a 32 byte bitfield */
		for (index = 0; index < 32; index++) {
			for (offset = 0; offset < 8; offset++) {
				if (ptr[index] & (1 << offset)) {
					(void)sctp_auth_add_chunk((index * 8) + offset, list);
				}
			}
		}
		size = 32;
	}
	return (size);
}