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
typedef  int /*<<< orphan*/  pcre_uchar ;

/* Variables and functions */
 scalar_t__ STRNCMP_UC_C8 (int /*<<< orphan*/  const*,char const*,unsigned int) ; 
 int* posix_name_lengths ; 
 char* posix_names ; 

__attribute__((used)) static int
check_posix_name(const pcre_uchar *ptr, int len)
{
const char *pn = posix_names;
register int yield = 0;
while (posix_name_lengths[yield] != 0)
  {
  if (len == posix_name_lengths[yield] &&
    STRNCMP_UC_C8(ptr, pn, (unsigned int)len) == 0) return yield;
  pn += posix_name_lengths[yield] + 1;
  yield++;
  }
return -1;
}