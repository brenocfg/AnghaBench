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
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int svn__ui64toa (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ui64toa_sep(apr_uint64_t number, char separator, char *buffer)
{
  apr_size_t length = svn__ui64toa(buffer, number);
  apr_size_t i;

  for (i = length; i > 3; i -= 3)
    {
      memmove(&buffer[i - 2], &buffer[i - 3], length - i + 3);
      buffer[i-3] = separator;
      length++;
    }

  buffer[length] = 0;
}