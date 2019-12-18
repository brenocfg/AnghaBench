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
struct fw_xferlist {int dummy; } ;
struct fw_xfer {int dummy; } ;

/* Variables and functions */
 struct fw_xfer* STAILQ_FIRST (struct fw_xferlist*) ; 
 int /*<<< orphan*/  STAILQ_INIT (struct fw_xferlist*) ; 
 struct fw_xfer* STAILQ_NEXT (struct fw_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_xfer_free_buf (struct fw_xfer*) ; 
 int /*<<< orphan*/  link ; 

void
fw_xferlist_remove(struct fw_xferlist *q)
{
	struct fw_xfer *xfer, *next;

	for (xfer = STAILQ_FIRST(q); xfer != NULL; xfer = next) {
		next = STAILQ_NEXT(xfer, link);
		fw_xfer_free_buf(xfer);
	}
	STAILQ_INIT(q);
}