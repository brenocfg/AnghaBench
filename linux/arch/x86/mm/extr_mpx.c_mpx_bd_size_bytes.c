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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned long MPX_BD_SIZE_BYTES_32 ; 
 unsigned long MPX_BD_SIZE_BYTES_64 ; 
 scalar_t__ is_64bit_mm (struct mm_struct*) ; 

__attribute__((used)) static inline unsigned long mpx_bd_size_bytes(struct mm_struct *mm)
{
	if (is_64bit_mm(mm))
		return MPX_BD_SIZE_BYTES_64;
	else
		return MPX_BD_SIZE_BYTES_32;
}