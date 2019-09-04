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
typedef  scalar_t__ Bool ;

/* Variables and functions */

__attribute__((used)) static void GetAttribString(UInt32 wa, Bool isDir, char *s)
{
  #ifdef USE_WINDOWS_FILE
  s[0] = (char)(((wa & FILE_ATTRIBUTE_DIRECTORY) != 0 || isDir) ? 'D' : '.');
  s[1] = (char)(((wa & FILE_ATTRIBUTE_READONLY ) != 0) ? 'R': '.');
  s[2] = (char)(((wa & FILE_ATTRIBUTE_HIDDEN   ) != 0) ? 'H': '.');
  s[3] = (char)(((wa & FILE_ATTRIBUTE_SYSTEM   ) != 0) ? 'S': '.');
  s[4] = (char)(((wa & FILE_ATTRIBUTE_ARCHIVE  ) != 0) ? 'A': '.');
  s[5] = 0;
  #else
  s[0] = (char)(((wa & (1 << 4)) != 0 || isDir) ? 'D' : '.');
  s[1] = 0;
  #endif
}