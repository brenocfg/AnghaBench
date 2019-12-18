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
 int /*<<< orphan*/  OPTIMIZER_HIDE_VAR (unsigned long) ; 

__attribute__((used)) static inline unsigned long __crypto_memneq_16(const void *a, const void *b)
{
	unsigned long neq = 0;

#ifdef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (sizeof(unsigned long) == 8) {
		neq |= *(unsigned long *)(a)   ^ *(unsigned long *)(b);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned long *)(a+8) ^ *(unsigned long *)(b+8);
		OPTIMIZER_HIDE_VAR(neq);
	} else if (sizeof(unsigned int) == 4) {
		neq |= *(unsigned int *)(a)    ^ *(unsigned int *)(b);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned int *)(a+4)  ^ *(unsigned int *)(b+4);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned int *)(a+8)  ^ *(unsigned int *)(b+8);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned int *)(a+12) ^ *(unsigned int *)(b+12);
		OPTIMIZER_HIDE_VAR(neq);
	} else
#endif /* CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS */
	{
		neq |= *(unsigned char *)(a)    ^ *(unsigned char *)(b);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+1)  ^ *(unsigned char *)(b+1);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+2)  ^ *(unsigned char *)(b+2);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+3)  ^ *(unsigned char *)(b+3);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+4)  ^ *(unsigned char *)(b+4);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+5)  ^ *(unsigned char *)(b+5);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+6)  ^ *(unsigned char *)(b+6);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+7)  ^ *(unsigned char *)(b+7);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+8)  ^ *(unsigned char *)(b+8);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+9)  ^ *(unsigned char *)(b+9);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+10) ^ *(unsigned char *)(b+10);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+11) ^ *(unsigned char *)(b+11);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+12) ^ *(unsigned char *)(b+12);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+13) ^ *(unsigned char *)(b+13);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+14) ^ *(unsigned char *)(b+14);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(unsigned char *)(a+15) ^ *(unsigned char *)(b+15);
		OPTIMIZER_HIDE_VAR(neq);
	}

	return neq;
}