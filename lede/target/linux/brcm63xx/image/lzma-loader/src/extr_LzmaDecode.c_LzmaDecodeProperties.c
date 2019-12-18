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
typedef  int UInt32 ;
struct TYPE_3__ {unsigned char lc; int DictionarySize; scalar_t__ lp; scalar_t__ pb; } ;
typedef  TYPE_1__ CLzmaProperties ;

/* Variables and functions */
 int LZMA_PROPERTIES_SIZE ; 
 int LZMA_RESULT_DATA_ERROR ; 
 int LZMA_RESULT_OK ; 

int LzmaDecodeProperties(CLzmaProperties *propsRes, const unsigned char *propsData, int size)
{
  unsigned char prop0;
  if (size < LZMA_PROPERTIES_SIZE)
    return LZMA_RESULT_DATA_ERROR;
  prop0 = propsData[0];
  if (prop0 >= (9 * 5 * 5))
    return LZMA_RESULT_DATA_ERROR;
  {
    for (propsRes->pb = 0; prop0 >= (9 * 5); propsRes->pb++, prop0 -= (9 * 5));
    for (propsRes->lp = 0; prop0 >= 9; propsRes->lp++, prop0 -= 9);
    propsRes->lc = prop0;
    /*
    unsigned char remainder = (unsigned char)(prop0 / 9);
    propsRes->lc = prop0 % 9;
    propsRes->pb = remainder / 5;
    propsRes->lp = remainder % 5;
    */
  }

  #ifdef _LZMA_OUT_READ
  {
    int i;
    propsRes->DictionarySize = 0;
    for (i = 0; i < 4; i++)
      propsRes->DictionarySize += (UInt32)(propsData[1 + i]) << (i * 8);
    if (propsRes->DictionarySize == 0)
      propsRes->DictionarySize = 1;
  }
  #endif
  return LZMA_RESULT_OK;
}