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
struct adrep {scalar_t__ adrp_byteorder; int /*<<< orphan*/  adrp_error; int /*<<< orphan*/  adrp_seq; } ;

/* Variables and functions */
 scalar_t__ ADIST_BYTEORDER ; 
 int /*<<< orphan*/  bswap16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bswap64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
adrep_decode_header(struct adrep *adrep)
{

	/* Byte-swap only if the receiver is using different byte order. */
	if (adrep->adrp_byteorder != ADIST_BYTEORDER) {
		adrep->adrp_byteorder = ADIST_BYTEORDER;
		adrep->adrp_seq = bswap64(adrep->adrp_seq);
		adrep->adrp_error = bswap16(adrep->adrp_error);
	}
}