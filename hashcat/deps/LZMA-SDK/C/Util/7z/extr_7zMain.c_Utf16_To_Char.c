#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt16 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {scalar_t__* data; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ CBuf ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_EnsureSize (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  SZ_ERROR_FAIL ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  Utf16_To_Utf8Buf (TYPE_1__*,scalar_t__ const*,unsigned int) ; 
 unsigned int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,char*,unsigned int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes Utf16_To_Char(CBuf *buf, const UInt16 *s
    #ifndef _USE_UTF8
    , UINT codePage
    #endif
    )
{
  unsigned len = 0;
  for (len = 0; s[len] != 0; len++);

  #ifndef _USE_UTF8
  {
    unsigned size = len * 3 + 100;
    if (!Buf_EnsureSize(buf, size))
      return SZ_ERROR_MEM;
    {
      buf->data[0] = 0;
      if (len != 0)
      {
        char defaultChar = '_';
        BOOL defUsed;
        unsigned numChars = 0;
        numChars = WideCharToMultiByte(codePage, 0, (LPCWSTR)s, len, (char *)buf->data, size, &defaultChar, &defUsed);
        if (numChars == 0 || numChars >= size)
          return SZ_ERROR_FAIL;
        buf->data[numChars] = 0;
      }
      return SZ_OK;
    }
  }
  #else
  return Utf16_To_Utf8Buf(buf, s, len);
  #endif
}