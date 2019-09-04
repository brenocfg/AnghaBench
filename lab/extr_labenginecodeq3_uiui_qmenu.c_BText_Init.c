#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ generic; } ;
typedef  TYPE_2__ menutext_s ;

/* Variables and functions */
 int /*<<< orphan*/  QMF_INACTIVE ; 

__attribute__((used)) static void BText_Init( menutext_s *t )
{
	t->generic.flags |= QMF_INACTIVE;
}