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
struct TYPE_2__ {int /*<<< orphan*/  output_stdout; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  glog ; 
 int /*<<< orphan*/  house_keeping () ; 
 int /*<<< orphan*/  output_logerrors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cleanup (int ret)
{
  /* done, restore tty modes and reset terminal into
   * non-visual mode */
  if (!conf.output_stdout)
    endwin ();

  /* unable to process valid data */
  if (ret)
    output_logerrors (glog);

  house_keeping ();
}