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

/* Variables and functions */
 unsigned int CK_HS_MODE_OBJECT ; 
 scalar_t__ CK_HS_VMA (void const*) ; 
 unsigned long CK_MD_VMA_BITS ; 

__attribute__((used)) static inline const void *
ck_hs_marshal(unsigned int mode, const void *key, unsigned long h)
{
#ifdef CK_HS_PP
	const void *insert;

	if (mode & CK_HS_MODE_OBJECT) {
		insert = (void *)((uintptr_t)CK_HS_VMA(key) |
		    ((h >> 25) << CK_MD_VMA_BITS));
	} else {
		insert = key;
	}

	return insert;
#else
	(void)mode;
	(void)h;

	return key;
#endif
}