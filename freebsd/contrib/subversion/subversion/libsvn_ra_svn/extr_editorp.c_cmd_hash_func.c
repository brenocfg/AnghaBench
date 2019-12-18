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
typedef  int apr_size_t ;
typedef  int apr_byte_t ;

/* Variables and functions */
 int CMD_HASH_SIZE ; 

__attribute__((used)) static apr_size_t
cmd_hash_func(const char *name,
              apr_size_t len)
{
  apr_size_t value =     (apr_byte_t)(name[0] - 'a') % 8
                   + 1 * (apr_byte_t)(name[len - 1] - 'a') % 8
                   + 10 * (len - 7);
  return value % CMD_HASH_SIZE;
}