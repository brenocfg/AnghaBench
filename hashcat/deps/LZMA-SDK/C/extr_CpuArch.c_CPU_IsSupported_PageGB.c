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
typedef  int /*<<< orphan*/  Cx86cpuid ;
typedef  int BoolInt ;

/* Variables and functions */
 int False ; 
 int /*<<< orphan*/  MyCPUID (int,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  x86cpuid_CheckAndRead (int /*<<< orphan*/ *) ; 

BoolInt CPU_IsSupported_PageGB()
{
  Cx86cpuid cpuid;
  if (!x86cpuid_CheckAndRead(&cpuid))
    return False;
  {
    UInt32 d[4] = { 0 };
    MyCPUID(0x80000000, &d[0], &d[1], &d[2], &d[3]);
    if (d[0] < 0x80000001)
      return False;
  }
  {
    UInt32 d[4] = { 0 };
    MyCPUID(0x80000001, &d[0], &d[1], &d[2], &d[3]);
    return (d[3] >> 26) & 1;
  }
}