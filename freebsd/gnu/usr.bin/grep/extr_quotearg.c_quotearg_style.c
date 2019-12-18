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
typedef  enum quoting_style { ____Placeholder_quoting_style } quoting_style ;

/* Variables and functions */
 char* quotearg_n_style (int /*<<< orphan*/ ,int,char const*) ; 

char *
quotearg_style (enum quoting_style s, char const *arg)
{
  return quotearg_n_style (0, s, arg);
}