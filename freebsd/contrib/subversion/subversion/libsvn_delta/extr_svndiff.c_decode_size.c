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

/* Variables and functions */
 scalar_t__ APR_SIZE_MAX ; 
 unsigned char* svn__decode_uint (scalar_t__*,unsigned char const*,unsigned char const*) ; 

__attribute__((used)) static const unsigned char *
decode_size(apr_size_t *val,
            const unsigned char *p,
            const unsigned char *end)
{
  apr_uint64_t temp = 0;
  const unsigned char *result = svn__decode_uint(&temp, p, end);
  if (temp > APR_SIZE_MAX)
    return NULL;

  *val = (apr_size_t)temp;
  return result;
}