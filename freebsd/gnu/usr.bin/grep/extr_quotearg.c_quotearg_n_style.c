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
struct quoting_options {int style; int /*<<< orphan*/  quote_these_too; } ;
typedef  enum quoting_style { ____Placeholder_quoting_style } quoting_style ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* quotearg_n_options (unsigned int,char const*,struct quoting_options*) ; 

char *
quotearg_n_style (unsigned int n, enum quoting_style s, char const *arg)
{
  struct quoting_options o;
  o.style = s;
  memset (o.quote_these_too, 0, sizeof o.quote_these_too);
  return quotearg_n_options (n, arg, &o);
}