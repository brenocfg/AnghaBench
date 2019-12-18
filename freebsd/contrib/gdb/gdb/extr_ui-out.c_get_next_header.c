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
struct TYPE_4__ {TYPE_1__* header_next; } ;
struct ui_out {TYPE_2__ table; } ;
struct TYPE_3__ {int colno; int width; int alignment; char* colhdr; struct TYPE_3__* next; } ;

/* Variables and functions */

__attribute__((used)) static int
get_next_header (struct ui_out *uiout,
		 int *colno,
		 int *width,
		 int *alignment,
		 char **colhdr)
{
  /* There may be no headers at all or we may have used all columns.  */
  if (uiout->table.header_next == NULL)
    return 0;
  *colno = uiout->table.header_next->colno;
  *width = uiout->table.header_next->width;
  *alignment = uiout->table.header_next->alignment;
  *colhdr = uiout->table.header_next->colhdr;
  /* Advance the header pointer to the next entry.  */
  uiout->table.header_next = uiout->table.header_next->next;
  return 1;
}