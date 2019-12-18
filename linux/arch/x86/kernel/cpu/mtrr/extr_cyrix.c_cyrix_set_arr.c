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
typedef  int mtrr_type ;

/* Variables and functions */
 unsigned int CX86_ARR_BASE ; 
 unsigned int CX86_RCR_BASE ; 
#define  MTRR_TYPE_UNCACHABLE 130 
#define  MTRR_TYPE_WRCOMB 129 
#define  MTRR_TYPE_WRTHROUGH 128 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  post_set () ; 
 int /*<<< orphan*/  prepare_set () ; 
 int /*<<< orphan*/  setCx86 (unsigned int,unsigned char) ; 

__attribute__((used)) static void cyrix_set_arr(unsigned int reg, unsigned long base,
			  unsigned long size, mtrr_type type)
{
	unsigned char arr, arr_type, arr_size;

	arr = CX86_ARR_BASE + (reg << 1) + reg;	/* avoid multiplication by 3 */

	/* count down from 32M (ARR0-ARR6) or from 2G (ARR7) */
	if (reg >= 7)
		size >>= 6;

	size &= 0x7fff;		/* make sure arr_size <= 14 */
	for (arr_size = 0; size; arr_size++, size >>= 1)
		;

	if (reg < 7) {
		switch (type) {
		case MTRR_TYPE_UNCACHABLE:
			arr_type = 1;
			break;
		case MTRR_TYPE_WRCOMB:
			arr_type = 9;
			break;
		case MTRR_TYPE_WRTHROUGH:
			arr_type = 24;
			break;
		default:
			arr_type = 8;
			break;
		}
	} else {
		switch (type) {
		case MTRR_TYPE_UNCACHABLE:
			arr_type = 0;
			break;
		case MTRR_TYPE_WRCOMB:
			arr_type = 8;
			break;
		case MTRR_TYPE_WRTHROUGH:
			arr_type = 25;
			break;
		default:
			arr_type = 9;
			break;
		}
	}

	prepare_set();

	base <<= PAGE_SHIFT;
	setCx86(arr + 0,  ((unsigned char *)&base)[3]);
	setCx86(arr + 1,  ((unsigned char *)&base)[2]);
	setCx86(arr + 2, (((unsigned char *)&base)[1]) | arr_size);
	setCx86(CX86_RCR_BASE + reg, arr_type);

	post_set();
}