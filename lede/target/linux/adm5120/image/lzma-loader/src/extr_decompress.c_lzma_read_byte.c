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
typedef  unsigned long SizeT ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 unsigned long FLASH_BANK_SIZE ; 
 int LZMA_RESULT_DATA_ERROR ; 
 int LZMA_RESULT_OK ; 
 unsigned char* flash_base ; 
 unsigned long flash_max ; 
 unsigned long flash_ofs ; 
 unsigned long flash_ofs_mask ; 

__attribute__((used)) static int lzma_read_byte(void *object, const unsigned char **buffer,
				SizeT *bufferSize)
{
	unsigned long len;

	if (flash_ofs >= flash_max)
		return LZMA_RESULT_DATA_ERROR;

	len = flash_max-flash_ofs;

#if (CONFIG_FLASH_SIZE > FLASH_BANK_SIZE)
	if (flash_ofs < FLASH_BANK_SIZE) {
		/* switch to bank 0 */
		DBG("lzma_read_byte: switch to bank 0\n");

		if (len > FLASH_BANK_SIZE-flash_ofs)
			len = FLASH_BANK_SIZE-flash_ofs;
	} else {
		/* switch to bank 1 */
		DBG("lzma_read_byte: switch to bank 1\n");
	}
#endif
	DBG("lzma_read_byte: ofs=%08X, len=%08X\n", flash_ofs, len);

	*buffer = flash_base+(flash_ofs & flash_ofs_mask);
	*bufferSize = len;
	flash_ofs += len;

	return LZMA_RESULT_OK;
}