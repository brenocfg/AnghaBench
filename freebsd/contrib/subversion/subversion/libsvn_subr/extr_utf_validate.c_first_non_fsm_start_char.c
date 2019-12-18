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
typedef  int apr_uintptr_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int const SVN__BIT_7_SET ; 

__attribute__((used)) static const char *
first_non_fsm_start_char(const char *data, apr_size_t max_len)
{
#if SVN_UNALIGNED_ACCESS_IS_OK

  /* Scan the input one machine word at a time. */
  for (; max_len > sizeof(apr_uintptr_t)
       ; data += sizeof(apr_uintptr_t), max_len -= sizeof(apr_uintptr_t))
    if (*(const apr_uintptr_t *)data & SVN__BIT_7_SET)
      break;

#endif

  /* The remaining odd bytes will be examined the naive way: */
  for (; max_len > 0; ++data, --max_len)
    if ((unsigned char)*data >= 0x80)
      break;

  return data;
}