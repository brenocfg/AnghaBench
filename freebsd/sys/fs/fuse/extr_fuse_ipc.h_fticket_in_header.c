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
struct TYPE_2__ {scalar_t__ base; } ;
struct fuse_ticket {TYPE_1__ tk_ms_fiov; } ;
struct fuse_in_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct fuse_in_header*
fticket_in_header(struct fuse_ticket *ftick)
{
	return (struct fuse_in_header *)(ftick->tk_ms_fiov.base);
}