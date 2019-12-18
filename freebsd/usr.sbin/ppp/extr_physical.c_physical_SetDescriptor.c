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
struct TYPE_2__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Read; int /*<<< orphan*/  IsSet; int /*<<< orphan*/  UpdateSet; int /*<<< orphan*/  type; } ;
struct physical {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYSICAL_DESCRIPTOR ; 
 int /*<<< orphan*/  physical_DescriptorRead ; 
 int /*<<< orphan*/  physical_DescriptorWrite ; 
 int /*<<< orphan*/  physical_IsSet ; 
 int /*<<< orphan*/  physical_UpdateSet ; 

void
physical_SetDescriptor(struct physical *p)
{
  p->desc.type = PHYSICAL_DESCRIPTOR;
  p->desc.UpdateSet = physical_UpdateSet;
  p->desc.IsSet = physical_IsSet;
  p->desc.Read = physical_DescriptorRead;
  p->desc.Write = physical_DescriptorWrite;
}