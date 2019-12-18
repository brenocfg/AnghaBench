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
struct ui_stream {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_stream_delete ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct ui_stream*) ; 

struct cleanup *
make_cleanup_ui_out_stream_delete (struct ui_stream *buf)
{
  return make_cleanup (do_stream_delete, buf);
}