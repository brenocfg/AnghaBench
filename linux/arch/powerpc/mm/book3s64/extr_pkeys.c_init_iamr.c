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
typedef  scalar_t__ u8 ;
typedef  int u64 ;

/* Variables and functions */
 int pkeyshift (int) ; 
 int read_iamr () ; 
 int /*<<< orphan*/  write_iamr (int) ; 

__attribute__((used)) static inline void init_iamr(int pkey, u8 init_bits)
{
	u64 new_iamr_bits = (((u64)init_bits & 0x1UL) << pkeyshift(pkey));
	u64 old_iamr = read_iamr() & ~((u64)(0x1ul) << pkeyshift(pkey));

	write_iamr(old_iamr | new_iamr_bits);
}