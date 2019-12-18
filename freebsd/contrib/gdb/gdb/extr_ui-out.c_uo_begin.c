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
typedef  enum ui_out_type { ____Placeholder_ui_out_type } ui_out_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* begin ) (struct ui_out*,int,int,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_out*,int,int,char const*) ; 

void
uo_begin (struct ui_out *uiout,
	  enum ui_out_type type,
	  int level,
	  const char *id)
{
  if (uiout->impl->begin == NULL)
    return;
  uiout->impl->begin (uiout, type, level, id);
}