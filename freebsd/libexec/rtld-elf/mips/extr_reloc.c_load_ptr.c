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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ Elf_Sxword ;
typedef  scalar_t__ Elf_Sword ;

/* Variables and functions */
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void*,size_t) ; 

__attribute__((used)) static __inline Elf_Sxword
load_ptr(void *where, size_t len)
{
	Elf_Sxword val;

	if (__predict_true(((uintptr_t)where & (len - 1)) == 0)) {
#ifdef __mips_n64
		if (len == sizeof(Elf_Sxword))
			return *(Elf_Sxword *)where;
#endif
		return *(Elf_Sword *)where;
	}

	val = 0;
#if BYTE_ORDER == LITTLE_ENDIAN
	(void)memcpy(&val, where, len);
#endif
#if BYTE_ORDER == BIG_ENDIAN
	(void)memcpy((uint8_t *)((&val)+1) - len, where, len);
#endif
	return (len == sizeof(Elf_Sxword)) ? val : (Elf_Sword)val;
}