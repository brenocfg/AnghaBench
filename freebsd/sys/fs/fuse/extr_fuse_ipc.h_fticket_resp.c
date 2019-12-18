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
struct fuse_iov {int dummy; } ;
struct fuse_ticket {struct fuse_iov tk_aw_fiov; } ;

/* Variables and functions */

__attribute__((used)) static inline struct fuse_iov *
fticket_resp(struct fuse_ticket *ftick)
{
	return (&ftick->tk_aw_fiov);
}