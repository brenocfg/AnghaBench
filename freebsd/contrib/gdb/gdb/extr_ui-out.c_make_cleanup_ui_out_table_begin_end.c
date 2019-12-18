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
 int /*<<< orphan*/  do_cleanup_table_end ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct ui_out*) ; 
 int /*<<< orphan*/  ui_out_table_begin (struct ui_out*,int,int,char const*) ; 

struct cleanup *
make_cleanup_ui_out_table_begin_end (struct ui_out *ui_out, int nr_cols,
                                     int nr_rows, const char *tblid)
{
  ui_out_table_begin (ui_out, nr_cols, nr_rows, tblid);
  return make_cleanup (do_cleanup_table_end, ui_out);
}