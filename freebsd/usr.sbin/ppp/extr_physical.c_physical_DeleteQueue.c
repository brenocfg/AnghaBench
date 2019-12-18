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
struct physical {int /*<<< orphan*/  link; int /*<<< orphan*/ * out; } ;

/* Variables and functions */
 int /*<<< orphan*/  link_DeleteQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

void
physical_DeleteQueue(struct physical *p)
{
  if (p->out) {
    m_freem(p->out);
    p->out = NULL;
  }
  link_DeleteQueue(&p->link);
}