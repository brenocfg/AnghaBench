#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ high; scalar_t__ low; } ;
typedef  TYPE_1__ SCI_SAS_ADDRESS_T ;
typedef  int S32 ;

/* Variables and functions */

__attribute__((used)) static
S32 sci_sas_address_compare(
   SCI_SAS_ADDRESS_T address_one,
   SCI_SAS_ADDRESS_T address_two
)
{
   if (address_one.high > address_two.high)
   {
      return 1;
   }
   else if (address_one.high < address_two.high)
   {
      return -1;
   }
   else if (address_one.low > address_two.low)
   {
      return 1;
   }
   else if (address_one.low < address_two.low)
   {
      return -1;
   }

   // The two SAS Address must be identical
   return 0;
}