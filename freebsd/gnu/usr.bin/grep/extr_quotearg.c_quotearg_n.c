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
 int /*<<< orphan*/  default_quoting_options ; 
 char* quotearg_n_options (unsigned int,char const*,int /*<<< orphan*/ *) ; 

char *
quotearg_n (unsigned int n, char const *arg)
{
  return quotearg_n_options (n, arg, &default_quoting_options);
}