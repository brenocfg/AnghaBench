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
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ memcmp (void const*,void const*,scalar_t__) ; 

__attribute__((used)) static svn_boolean_t
equal(const void *left, apr_size_t left_len,
      const void *right, apr_size_t right_len)
{
  if (left_len != right_len)
    return FALSE;

  return memcmp(left, right, right_len) == 0;
}