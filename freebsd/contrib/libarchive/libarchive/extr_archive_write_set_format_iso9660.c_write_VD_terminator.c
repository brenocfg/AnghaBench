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
struct archive_write {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGICAL_BLOCK_SIZE ; 
 int /*<<< orphan*/  VDT_TERMINATOR ; 
 int /*<<< orphan*/  set_VD_bp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_unused_field_bp (unsigned char*,int,int /*<<< orphan*/ ) ; 
 unsigned char* wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
write_VD_terminator(struct archive_write *a)
{
	unsigned char *bp;

	bp = wb_buffptr(a) -1;
	set_VD_bp(bp, VDT_TERMINATOR, 1);
	set_unused_field_bp(bp, 8, LOGICAL_BLOCK_SIZE);

	return (wb_consume(a, LOGICAL_BLOCK_SIZE));
}