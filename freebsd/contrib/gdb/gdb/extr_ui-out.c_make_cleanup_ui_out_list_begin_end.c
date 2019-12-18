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
struct cleanup {int dummy; } ;

/* Variables and functions */
 struct cleanup* make_cleanup_ui_out_end (struct ui_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_begin (struct ui_out*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ui_out_type_list ; 

struct cleanup *
make_cleanup_ui_out_list_begin_end (struct ui_out *uiout,
				    const char *id)
{
  ui_out_begin (uiout, ui_out_type_list, id);
  return make_cleanup_ui_out_end (uiout, ui_out_type_list);
}