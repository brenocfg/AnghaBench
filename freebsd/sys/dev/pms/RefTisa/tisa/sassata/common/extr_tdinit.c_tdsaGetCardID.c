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
typedef  int /*<<< orphan*/  tiRoot_t ;
typedef  size_t bit32 ;

/* Variables and functions */
 scalar_t__ TD_CARD_ID_ALLOC ; 
 scalar_t__ TD_CARD_ID_FREE ; 
 size_t TD_MAX_CARD_NUM ; 
 scalar_t__* tdCardIDList ; 

bit32 tdsaGetCardID(tiRoot_t * tiRoot)
{
  bit32 i;
  bit32 RetVal = 0xFFFFFFFF;

  for (i = 0 ; i < TD_MAX_CARD_NUM ; i++)
  {
    if (tdCardIDList[i] == TD_CARD_ID_FREE)
    {
      tdCardIDList[i] = TD_CARD_ID_ALLOC;
      RetVal = i;
      break;
    }
  }

  return RetVal;

}