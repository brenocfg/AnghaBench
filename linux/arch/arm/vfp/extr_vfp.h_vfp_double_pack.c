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
typedef  int u64 ;
struct vfp_double {int significand; scalar_t__ exponent; scalar_t__ sign; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int VFP_DOUBLE_LOW_BITS ; 
 int VFP_DOUBLE_MANTISSA_BITS ; 

__attribute__((used)) static inline s64 vfp_double_pack(struct vfp_double *s)
{
	u64 val;
	val = ((u64)s->sign << 48) +
	      ((u64)s->exponent << VFP_DOUBLE_MANTISSA_BITS) +
	      (s->significand >> VFP_DOUBLE_LOW_BITS);
	return (s64)val;
}