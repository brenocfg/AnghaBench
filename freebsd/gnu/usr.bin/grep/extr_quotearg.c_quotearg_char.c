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
struct quoting_options {int dummy; } ;

/* Variables and functions */
 struct quoting_options default_quoting_options ; 
 char* quotearg_n_options (int /*<<< orphan*/ ,char const*,struct quoting_options*) ; 
 int /*<<< orphan*/  set_char_quoting (struct quoting_options*,char,int) ; 

char *
quotearg_char (char const *arg, char ch)
{
  struct quoting_options options;
  options = default_quoting_options;
  set_char_quoting (&options, ch, 1);
  return quotearg_n_options (0, arg, &options);
}