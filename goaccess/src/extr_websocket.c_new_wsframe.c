#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int reading; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ WSFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* xcalloc (int,int) ; 

__attribute__((used)) static WSFrame *
new_wsframe (void)
{
  WSFrame *frame = xcalloc (1, sizeof (WSFrame));
  memset (frame->buf, 0, sizeof (frame->buf));
  frame->reading = 1;

  return frame;
}