#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_write_fn_t ;
struct TYPE_3__ {int /*<<< orphan*/  write_fn; } ;
typedef  TYPE_1__ svn_stream_t ;

/* Variables and functions */

void
svn_stream_set_write(svn_stream_t *stream, svn_write_fn_t write_fn)
{
  stream->write_fn = write_fn;
}