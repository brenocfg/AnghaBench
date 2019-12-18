#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Properties; } ;
typedef  int SizeT ;

/* Variables and functions */
 int LZMA_PROPERTIES_SIZE ; 
 int LzmaDecodeProperties (int /*<<< orphan*/ *,unsigned char*,int) ; 
 unsigned char lzma_get_byte () ; 
 int lzma_outsize ; 
 TYPE_1__ lzma_state ; 

__attribute__((used)) static int lzma_init_props(void)
{
	unsigned char props[LZMA_PROPERTIES_SIZE];
	int res;
	int i;

	/* read lzma properties */
	for (i = 0; i < LZMA_PROPERTIES_SIZE; i++)
		props[i] = lzma_get_byte();

	/* read the lower half of uncompressed size in the header */
	lzma_outsize = ((SizeT) lzma_get_byte()) +
		       ((SizeT) lzma_get_byte() << 8) +
		       ((SizeT) lzma_get_byte() << 16) +
		       ((SizeT) lzma_get_byte() << 24);

	/* skip rest of the header (upper half of uncompressed size) */
	for (i = 0; i < 4; i++)
		lzma_get_byte();

	res = LzmaDecodeProperties(&lzma_state.Properties, props,
					LZMA_PROPERTIES_SIZE);
	return res;
}