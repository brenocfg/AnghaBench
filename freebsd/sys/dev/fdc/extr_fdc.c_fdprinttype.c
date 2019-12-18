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
struct fd_type {int sectrac; int secsize; int datalen; int gap; int tracks; int size; int trans; int heads; int f_gap; int f_inter; int offset_side2; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void
fdprinttype(struct fd_type *ft)
{

	printf("(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,0x%x)",
	    ft->sectrac, ft->secsize, ft->datalen, ft->gap, ft->tracks,
	    ft->size, ft->trans, ft->heads, ft->f_gap, ft->f_inter,
	    ft->offset_side2, ft->flags);
}