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
struct ui_out {int dummy; } ;
struct ui_file {int dummy; } ;

/* Variables and functions */
 int uo_redirect (struct ui_out*,struct ui_file*) ; 

int
ui_out_redirect (struct ui_out *uiout, struct ui_file *outstream)
{
  return uo_redirect (uiout, outstream);
}