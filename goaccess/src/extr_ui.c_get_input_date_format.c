#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ date_format; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 char* escape_str (scalar_t__) ; 

__attribute__((used)) static char *
get_input_date_format (void)
{
  char *date_format = NULL;

  if (conf.date_format)
    date_format = escape_str (conf.date_format);
  return date_format;
}