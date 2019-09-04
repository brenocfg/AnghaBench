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
typedef  int WRes ;
struct TYPE_3__ {int /*<<< orphan*/  file; } ;
typedef  scalar_t__ Int64 ;
typedef  int ESzSeek ;
typedef  TYPE_1__ CSzFile ;

/* Variables and functions */
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
#define  SZ_SEEK_CUR 130 
#define  SZ_SEEK_END 129 
#define  SZ_SEEK_SET 128 
 int fseek (int /*<<< orphan*/ ,long,int) ; 
 scalar_t__ ftell (int /*<<< orphan*/ ) ; 

WRes File_Seek(CSzFile *p, Int64 *pos, ESzSeek origin)
{
  #ifdef USE_WINDOWS_FILE

  LARGE_INTEGER value;
  DWORD moveMethod;
  value.LowPart = (DWORD)*pos;
  value.HighPart = (LONG)((UInt64)*pos >> 16 >> 16); /* for case when UInt64 is 32-bit only */
  switch (origin)
  {
    case SZ_SEEK_SET: moveMethod = FILE_BEGIN; break;
    case SZ_SEEK_CUR: moveMethod = FILE_CURRENT; break;
    case SZ_SEEK_END: moveMethod = FILE_END; break;
    default: return ERROR_INVALID_PARAMETER;
  }
  value.LowPart = SetFilePointer(p->handle, value.LowPart, &value.HighPart, moveMethod);
  if (value.LowPart == 0xFFFFFFFF)
  {
    WRes res = GetLastError();
    if (res != NO_ERROR)
      return res;
  }
  *pos = ((Int64)value.HighPart << 32) | value.LowPart;
  return 0;

  #else
  
  int moveMethod;
  int res;
  switch (origin)
  {
    case SZ_SEEK_SET: moveMethod = SEEK_SET; break;
    case SZ_SEEK_CUR: moveMethod = SEEK_CUR; break;
    case SZ_SEEK_END: moveMethod = SEEK_END; break;
    default: return 1;
  }
  res = fseek(p->file, (long)*pos, moveMethod);
  *pos = ftell(p->file);
  return res;
  
  #endif
}