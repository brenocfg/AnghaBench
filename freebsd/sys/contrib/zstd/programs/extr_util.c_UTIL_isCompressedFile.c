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

/* Variables and functions */
 char* UTIL_getFileExtension (char const*) ; 
 int strcmp (char const*,char const*) ; 

int UTIL_isCompressedFile(const char *inputName, const char *extensionList[])
{
  const char* ext = UTIL_getFileExtension(inputName);
  while(*extensionList!=NULL)
  {
    const int isCompressedExtension = strcmp(ext,*extensionList);
    if(isCompressedExtension==0)
      return 1;
    ++extensionList;
  }
   return 0;
}