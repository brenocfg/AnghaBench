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
typedef  int /*<<< orphan*/  va_list ;
struct ui_out {TYPE_1__* impl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* message ) (struct ui_out*,int,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_out*,int,char const*,int /*<<< orphan*/ ) ; 

void
uo_message (struct ui_out *uiout, int verbosity,
	    const char *format,
	    va_list args)
{
  if (!uiout->impl->message)
    return;
  uiout->impl->message (uiout, verbosity, format, args);
}