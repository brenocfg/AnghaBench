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
struct fuse_ticket {int dummy; } ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;
struct TYPE_2__ {int opcode; } ;

/* Variables and functions */
 TYPE_1__* fticket_in_header (struct fuse_ticket*) ; 

__attribute__((used)) static inline enum fuse_opcode
fticket_opcode(struct fuse_ticket *ftick)
{
	return fticket_in_header(ftick)->opcode;
}