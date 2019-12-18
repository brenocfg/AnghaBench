#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iso9660_disk ;
struct TYPE_6__ {TYPE_1__* isoDirRecord; } ;
typedef  TYPE_2__ cd9660node ;
struct TYPE_5__ {scalar_t__* length; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ cd9660_susp_handle_continuation_common (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static int
cd9660_susp_handle_continuation(iso9660_disk *diskStructure, cd9660node *node)
{
	assert (node != NULL);

	/* Entry */
	if (cd9660_susp_handle_continuation_common(diskStructure,
		node,(int)(node->isoDirRecord->length[0])) < 0)
		return 0;

	return 1;
}