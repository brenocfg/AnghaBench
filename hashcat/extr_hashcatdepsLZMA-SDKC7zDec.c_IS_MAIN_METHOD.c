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
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
#define  k_Copy 130 
#define  k_LZMA 129 
#define  k_LZMA2 128 

__attribute__((used)) static Bool IS_MAIN_METHOD(UInt32 m)
{
  switch (m)
  {
    case k_Copy:
    case k_LZMA:
    #ifndef _7Z_NO_METHOD_LZMA2
    case k_LZMA2:
    #endif
    #ifdef _7ZIP_PPMD_SUPPPORT
    case k_PPMD:
    #endif
      return True;
  }
  return False;
}