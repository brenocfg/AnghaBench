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
struct quoting_options {int style; } ;
typedef  enum quoting_style { ____Placeholder_quoting_style } quoting_style ;

/* Variables and functions */
 struct quoting_options default_quoting_options ; 

void
set_quoting_style (struct quoting_options *o, enum quoting_style s)
{
  (o ? o : &default_quoting_options)->style = s;
}