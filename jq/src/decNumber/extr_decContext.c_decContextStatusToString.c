#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ status; } ;
typedef  TYPE_1__ decContext ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 scalar_t__ DEC_Clamped ; 
 char const* DEC_Condition_CS ; 
 char const* DEC_Condition_DI ; 
 char const* DEC_Condition_DU ; 
 char const* DEC_Condition_DZ ; 
 char const* DEC_Condition_IC ; 
 char const* DEC_Condition_IE ; 
 char const* DEC_Condition_IO ; 
 char const* DEC_Condition_IS ; 
 char const* DEC_Condition_LD ; 
 char const* DEC_Condition_MU ; 
 char const* DEC_Condition_OV ; 
 char const* DEC_Condition_PA ; 
 char const* DEC_Condition_RO ; 
 char const* DEC_Condition_SU ; 
 char const* DEC_Condition_UN ; 
 char const* DEC_Condition_ZE ; 
 scalar_t__ DEC_Conversion_syntax ; 
 scalar_t__ DEC_Division_by_zero ; 
 scalar_t__ DEC_Division_impossible ; 
 scalar_t__ DEC_Division_undefined ; 
 scalar_t__ DEC_Inexact ; 
 scalar_t__ DEC_Insufficient_storage ; 
 scalar_t__ DEC_Invalid_context ; 
 scalar_t__ DEC_Invalid_operation ; 
 scalar_t__ DEC_Lost_digits ; 
 scalar_t__ DEC_Overflow ; 
 scalar_t__ DEC_Rounded ; 
 scalar_t__ DEC_Subnormal ; 
 scalar_t__ DEC_Underflow ; 

const char *decContextStatusToString(const decContext *context) {
  Int status=context->status;

  // test the five IEEE first, as some of the others are ambiguous when
  // DECEXTFLAG=0
  if (status==DEC_Invalid_operation    ) return DEC_Condition_IO;
  if (status==DEC_Division_by_zero     ) return DEC_Condition_DZ;
  if (status==DEC_Overflow             ) return DEC_Condition_OV;
  if (status==DEC_Underflow            ) return DEC_Condition_UN;
  if (status==DEC_Inexact              ) return DEC_Condition_IE;

  if (status==DEC_Division_impossible  ) return DEC_Condition_DI;
  if (status==DEC_Division_undefined   ) return DEC_Condition_DU;
  if (status==DEC_Rounded              ) return DEC_Condition_RO;
  if (status==DEC_Clamped              ) return DEC_Condition_PA;
  if (status==DEC_Subnormal            ) return DEC_Condition_SU;
  if (status==DEC_Conversion_syntax    ) return DEC_Condition_CS;
  if (status==DEC_Insufficient_storage ) return DEC_Condition_IS;
  if (status==DEC_Invalid_context      ) return DEC_Condition_IC;
  #if DECSUBSET
  if (status==DEC_Lost_digits          ) return DEC_Condition_LD;
  #endif
  if (status==0                        ) return DEC_Condition_ZE;
  return DEC_Condition_MU;  // Multiple errors
  }