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
struct bhnd_nvram_tlv {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,size_t,int) ; 
 uintptr_t SIZE_MAX ; 
 size_t bhnd_nvram_io_getsize (int /*<<< orphan*/ ) ; 
 int bhnd_nvram_io_read_ptr (int /*<<< orphan*/ ,int,void const**,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
bhnd_nvram_tlv_to_offset(struct bhnd_nvram_tlv *tlv, void *cookiep)
{
	const void	*ptr;
	intptr_t	 offset;
	size_t		 io_size;
	int		 error;

	BHND_NV_ASSERT(cookiep != NULL, ("null cookiep"));

	io_size = bhnd_nvram_io_getsize(tlv->data);

	error = bhnd_nvram_io_read_ptr(tlv->data, 0x0, &ptr, io_size, NULL);
	if (error)
		BHND_NV_PANIC("error mapping offset %zu: %d", io_size, error);

	offset = (const uint8_t *)cookiep - (const uint8_t *)ptr;
	BHND_NV_ASSERT(offset >= 0, ("invalid cookiep"));
	BHND_NV_ASSERT((uintptr_t)offset < SIZE_MAX, ("cookiep > SIZE_MAX)"));
	BHND_NV_ASSERT((uintptr_t)offset <= io_size, ("cookiep > io_size)"));

	return ((size_t)offset);
}