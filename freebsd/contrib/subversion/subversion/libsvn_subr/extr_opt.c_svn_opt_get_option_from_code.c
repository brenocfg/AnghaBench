#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t apr_size_t ;
struct TYPE_4__ {int optch; } ;
typedef  TYPE_1__ apr_getopt_option_t ;

/* Variables and functions */

const apr_getopt_option_t *
svn_opt_get_option_from_code(int code,
                             const apr_getopt_option_t *option_table)
{
  apr_size_t i;

  for (i = 0; option_table[i].optch; i++)
    if (option_table[i].optch == code)
      return &(option_table[i]);

  return NULL;
}