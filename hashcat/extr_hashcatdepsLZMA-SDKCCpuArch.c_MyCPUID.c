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
typedef  int UInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  __cpuid (int*,int) ; 

void MyCPUID(UInt32 function, UInt32 *a, UInt32 *b, UInt32 *c, UInt32 *d)
{
  #ifdef USE_ASM

  #ifdef _MSC_VER

  UInt32 a2, b2, c2, d2;
  __asm xor EBX, EBX;
  __asm xor ECX, ECX;
  __asm xor EDX, EDX;
  __asm mov EAX, function;
  __asm cpuid;
  __asm mov a2, EAX;
  __asm mov b2, EBX;
  __asm mov c2, ECX;
  __asm mov d2, EDX;

  *a = a2;
  *b = b2;
  *c = c2;
  *d = d2;

  #else

  __asm__ __volatile__ (
  #if defined(MY_CPU_AMD64) && defined(__PIC__)
    "mov %%rbx, %%rdi;"
    "cpuid;"
    "xchg %%rbx, %%rdi;"
    : "=a" (*a) ,
      "=D" (*b) ,
  #elif defined(MY_CPU_X86) && defined(__PIC__)
    "mov %%ebx, %%edi;"
    "cpuid;"
    "xchgl %%ebx, %%edi;"
    : "=a" (*a) ,
      "=D" (*b) ,
  #else
    "cpuid"
    : "=a" (*a) ,
      "=b" (*b) ,
  #endif
      "=c" (*c) ,
      "=d" (*d)
    : "0" (function)) ;

  #endif
  
  #else

  int CPUInfo[4];
  __cpuid(CPUInfo, function);
  *a = CPUInfo[0];
  *b = CPUInfo[1];
  *c = CPUInfo[2];
  *d = CPUInfo[3];

  #endif
}