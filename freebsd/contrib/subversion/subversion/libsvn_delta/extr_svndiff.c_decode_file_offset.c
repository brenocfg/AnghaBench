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
typedef  scalar_t__ svn_filesize_t ;
typedef  scalar_t__ apr_uint64_t ;

/* Variables and functions */
 unsigned char* svn__decode_uint (scalar_t__*,unsigned char const*,unsigned char const*) ; 

__attribute__((used)) static const unsigned char *
decode_file_offset(svn_filesize_t *val,
                   const unsigned char *p,
                   const unsigned char *end)
{
  apr_uint64_t temp = 0;
  const unsigned char *result = svn__decode_uint(&temp, p, end);
  *val = (svn_filesize_t)temp;

  return result;
}