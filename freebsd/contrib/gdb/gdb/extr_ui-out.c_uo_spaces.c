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
struct ui_out {TYPE_1__* impl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* spaces ) (struct ui_out*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_out*,int) ; 

void
uo_spaces (struct ui_out *uiout, int numspaces)
{
  if (!uiout->impl->spaces)
    return;
  uiout->impl->spaces (uiout, numspaces);
}