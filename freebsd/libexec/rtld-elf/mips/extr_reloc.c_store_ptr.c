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
typedef  int /*<<< orphan*/  const Elf_Sxword ;
typedef  int /*<<< orphan*/  Elf_Sword ;

/* Variables and functions */
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static __inline void
store_ptr(void *where, Elf_Sxword val, size_t len)
{
	if (__predict_true(((uintptr_t)where & (len - 1)) == 0)) {
#ifdef __mips_n64
		if (len == sizeof(Elf_Sxword)) {
			*(Elf_Sxword *)where = val;
			return;
		}
#endif
		*(Elf_Sword *)where = val;
		return;
	}
#if BYTE_ORDER == LITTLE_ENDIAN
	(void)memcpy(where, &val, len);
#endif
#if BYTE_ORDER == BIG_ENDIAN
	(void)memcpy(where, (const uint8_t *)((&val)+1) - len, len);
#endif
}