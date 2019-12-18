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
struct mp {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 size_t link_QueueLen (int /*<<< orphan*/ *) ; 

size_t
mp_QueueLen(struct mp *mp)
{
  return link_QueueLen(&mp->link);
}