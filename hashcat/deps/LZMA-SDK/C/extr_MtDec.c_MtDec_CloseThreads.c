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
struct TYPE_3__ {int /*<<< orphan*/ * threads; } ;
typedef  TYPE_1__ CMtDec ;

/* Variables and functions */
 unsigned int MTDEC__THREADS_MAX ; 
 int /*<<< orphan*/  MtDecThread_CloseThread (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MtDec_CloseThreads(CMtDec *p)
{
  unsigned i;
  for (i = 0; i < MTDEC__THREADS_MAX; i++)
    MtDecThread_CloseThread(&p->threads[i]);
}