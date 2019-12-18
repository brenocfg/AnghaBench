#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int R_EAX; int R_EBX; int R_ECX; int R_EDX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_cpuid (int*,int*,int*,int*) ; 

__attribute__((used)) static void
x86emuOp2_cpuid(struct x86emu *emu)
{
#if defined(__i386__) || defined(__amd64__)
	hw_cpuid(&emu->x86.R_EAX, &emu->x86.R_EBX, &emu->x86.R_ECX,
	    &emu->x86.R_EDX);
#endif
	switch (emu->x86.R_EAX) {
	case 0:
		emu->x86.R_EAX = 1;
#if !defined(__i386__) && !defined(__amd64__)
		/* "GenuineIntel" */
		emu->x86.R_EBX = 0x756e6547;
		emu->x86.R_EDX = 0x49656e69;
		emu->x86.R_ECX = 0x6c65746e;
#endif
		break;
	case 1:
#if !defined(__i386__) && !defined(__amd64__)
		emu->x86.R_EAX = 0x00000480;
		emu->x86.R_EBX = emu->x86.R_ECX = 0;
		emu->x86.R_EDX = 0x00000002;
#else
		emu->x86.R_EDX &= 0x00000012;
#endif
		break;
	default:
		emu->x86.R_EAX = emu->x86.R_EBX = emu->x86.R_ECX =
		    emu->x86.R_EDX = 0;
		break;
	}
}