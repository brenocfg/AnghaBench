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
typedef  scalar_t__ u_char ;
struct address {scalar_t__ selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXCEPTION (int) ; 
 int EX_INTERNAL ; 
 int /*<<< orphan*/  FPU_info ; 
 scalar_t__ PREFIX_SS_ ; 
 int /*<<< orphan*/  SIGSEGV ; 
 scalar_t__ VM86_REG_ (scalar_t__) ; 
 int /*<<< orphan*/  math_abort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long vm86_segment(u_char segment, struct address *addr)
{
	segment--;
#ifdef PARANOID
	if (segment > PREFIX_SS_) {
		EXCEPTION(EX_INTERNAL | 0x130);
		math_abort(FPU_info, SIGSEGV);
	}
#endif /* PARANOID */
	addr->selector = VM86_REG_(segment);
	return (unsigned long)VM86_REG_(segment) << 4;
}