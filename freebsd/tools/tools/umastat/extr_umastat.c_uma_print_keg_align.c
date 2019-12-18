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
struct uma_keg {int uk_align; } ;

/* Variables and functions */
#define  UMA_ALIGN_CACHE 133 
#define  UMA_ALIGN_CHAR 132 
#define  UMA_ALIGN_INT 131 
#define  UMA_ALIGN_LONG 130 
#define  UMA_ALIGN_PTR 129 
#define  UMA_ALIGN_SHORT 128 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 

__attribute__((used)) static void
uma_print_keg_align(struct uma_keg *ukp, const char *spaces)
{

	switch(ukp->uk_align) {
	case UMA_ALIGN_PTR:
		printf("%suk_align = UMA_ALIGN_PTR;\n", spaces);
		break;

#if 0
	case UMA_ALIGN_LONG:
		printf("%suk_align = UMA_ALIGN_LONG;\n", spaces);
		break;

	case UMA_ALIGN_INT:
		printf("%suk_align = UMA_ALIGN_INT;\n", spaces);
		break;
#endif

	case UMA_ALIGN_SHORT:
		printf("%suk_align = UMA_ALIGN_SHORT;\n", spaces);
		break;

	case UMA_ALIGN_CHAR:
		printf("%suk_align = UMA_ALIGN_CHAR;\n", spaces);
		break;

	case UMA_ALIGN_CACHE:
		printf("%suk_align = UMA_ALIGN_CACHE;\n", spaces);
		break;

	default:
		printf("%suk_align = %d\n", spaces, ukp->uk_align);
	}
}