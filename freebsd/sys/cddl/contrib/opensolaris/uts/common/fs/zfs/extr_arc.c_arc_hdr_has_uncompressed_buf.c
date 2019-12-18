#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {struct TYPE_7__* b_next; } ;
typedef  TYPE_2__ arc_buf_t ;
struct TYPE_6__ {TYPE_2__* b_buf; } ;
struct TYPE_8__ {TYPE_1__ b_l1hdr; } ;
typedef  TYPE_3__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_BUF_COMPRESSED (TYPE_2__*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 

__attribute__((used)) static boolean_t
arc_hdr_has_uncompressed_buf(arc_buf_hdr_t *hdr)
{
	for (arc_buf_t *b = hdr->b_l1hdr.b_buf; b != NULL; b = b->b_next) {
		if (!ARC_BUF_COMPRESSED(b)) {
			return (B_TRUE);
		}
	}
	return (B_FALSE);
}