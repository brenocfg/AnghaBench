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
typedef  scalar_t__ UInt64 ;
typedef  int /*<<< orphan*/  CSzFile ;
typedef  char Byte ;
typedef  int /*<<< orphan*/  BoolInt ;

/* Variables and functions */
 scalar_t__ CrcCalc (char*,int) ; 
 int /*<<< orphan*/  False ; 
 scalar_t__ File_Read (int /*<<< orphan*/ *,char*,size_t*) ; 
 scalar_t__ GetUi32 (char*) ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  k7zSignature ; 
 int /*<<< orphan*/  k7zSignatureSize ; 
 size_t k7zStartHeaderSize ; 
 int kBufferSize ; 
 scalar_t__ kSignatureSearchLimit ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 

__attribute__((used)) static BoolInt FindSignature(CSzFile *stream, UInt64 *resPos)
{
  Byte buf[kBufferSize];
  size_t numPrevBytes = 0;
  *resPos = 0;
  for (;;)
  {
    size_t processed, pos;
    if (*resPos > kSignatureSearchLimit)
      return False;
    processed = kBufferSize - numPrevBytes;
    if (File_Read(stream, buf + numPrevBytes, &processed) != 0)
      return False;
    processed += numPrevBytes;
    if (processed < k7zStartHeaderSize ||
        (processed == k7zStartHeaderSize && numPrevBytes != 0))
      return False;
    processed -= k7zStartHeaderSize;
    for (pos = 0; pos <= processed; pos++)
    {
      for (; pos <= processed && buf[pos] != '7'; pos++);
      if (pos > processed)
        break;
      if (memcmp(buf + pos, k7zSignature, k7zSignatureSize) == 0)
        if (CrcCalc(buf + pos + 12, 20) == GetUi32(buf + pos + 8))
        {
          *resPos += pos;
          return True;
        }
    }
    *resPos += processed;
    numPrevBytes = k7zStartHeaderSize;
    memmove(buf, buf + processed, k7zStartHeaderSize);
  }
}