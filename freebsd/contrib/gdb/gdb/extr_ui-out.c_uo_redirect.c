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
struct ui_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* redirect ) (struct ui_out*,struct ui_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_out*,struct ui_file*) ; 

int
uo_redirect (struct ui_out *uiout, struct ui_file *outstream)
{
  if (!uiout->impl->redirect)
    return -1;
  uiout->impl->redirect (uiout, outstream);
  return 0;
}