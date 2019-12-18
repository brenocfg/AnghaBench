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
struct TYPE_2__ {char* date_num_format; char* spec_date_time_num_format; scalar_t__ date_spec_hr; } ;

/* Variables and functions */
 char* append_spec_date_format (char const*,char*) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 char* set_format_time () ; 
 scalar_t__ strchr (char*,char) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
set_spec_date_time_num_format (void)
{
  char *buf = NULL, *tf = set_format_time ();
  const char *df = conf.date_num_format;

  if (!df || !tf)
    return;

  if (conf.date_spec_hr && strchr (tf, 'H'))
    buf = append_spec_date_format (df, "%H");
  else
    buf = xstrdup (df);

  conf.spec_date_time_num_format = buf;
  free (tf);
}