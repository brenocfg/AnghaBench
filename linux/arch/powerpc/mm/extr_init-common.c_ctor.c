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
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int MAX_PGTABLE_INDEX_SIZE ; 
 void ctor_0 (void*) ; 
 void ctor_1 (void*) ; 
 void ctor_10 (void*) ; 
 void ctor_11 (void*) ; 
 void ctor_12 (void*) ; 
 void ctor_13 (void*) ; 
 void ctor_14 (void*) ; 
 void ctor_15 (void*) ; 
 void ctor_2 (void*) ; 
 void ctor_3 (void*) ; 
 void ctor_4 (void*) ; 
 void ctor_5 (void*) ; 
 void ctor_6 (void*) ; 
 void ctor_7 (void*) ; 
 void ctor_8 (void*) ; 
 void ctor_9 (void*) ; 

__attribute__((used)) static inline void (*ctor(int shift))(void *)
{
	BUILD_BUG_ON(MAX_PGTABLE_INDEX_SIZE != 15);

	switch (shift) {
	case 0: return ctor_0;
	case 1: return ctor_1;
	case 2: return ctor_2;
	case 3: return ctor_3;
	case 4: return ctor_4;
	case 5: return ctor_5;
	case 6: return ctor_6;
	case 7: return ctor_7;
	case 8: return ctor_8;
	case 9: return ctor_9;
	case 10: return ctor_10;
	case 11: return ctor_11;
	case 12: return ctor_12;
	case 13: return ctor_13;
	case 14: return ctor_14;
	case 15: return ctor_15;
	}
	return NULL;
}