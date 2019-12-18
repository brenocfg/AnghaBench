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
typedef  scalar_t__ apr_uint64_t ;
typedef  scalar_t__ apr_size_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 scalar_t__ svn__ui64toa (char*,scalar_t__) ; 

apr_size_t
svn__i64toa(char * dest, apr_int64_t number)
{
  if (number >= 0)
    return svn__ui64toa(dest, (apr_uint64_t)number);

  *dest = '-';
  return svn__ui64toa(dest + 1, 0 - (apr_uint64_t)number) + 1;
}