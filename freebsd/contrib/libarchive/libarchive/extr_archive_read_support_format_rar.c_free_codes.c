#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  table; int /*<<< orphan*/  tree; } ;
struct rar {TYPE_2__ lengthcode; TYPE_2__ lowoffsetcode; TYPE_2__ offsetcode; TYPE_2__ maincode; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
free_codes(struct archive_read *a)
{
  struct rar *rar = (struct rar *)(a->format->data);
  free(rar->maincode.tree);
  free(rar->offsetcode.tree);
  free(rar->lowoffsetcode.tree);
  free(rar->lengthcode.tree);
  free(rar->maincode.table);
  free(rar->offsetcode.table);
  free(rar->lowoffsetcode.table);
  free(rar->lengthcode.table);
  memset(&rar->maincode, 0, sizeof(rar->maincode));
  memset(&rar->offsetcode, 0, sizeof(rar->offsetcode));
  memset(&rar->lowoffsetcode, 0, sizeof(rar->lowoffsetcode));
  memset(&rar->lengthcode, 0, sizeof(rar->lengthcode));
}