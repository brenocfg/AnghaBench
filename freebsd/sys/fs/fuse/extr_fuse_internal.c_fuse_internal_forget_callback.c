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
struct uio {int dummy; } ;
struct TYPE_4__ {scalar_t__ base; } ;
struct fuse_ticket {TYPE_2__ tk_ms_fiov; TYPE_1__* tk_data; } ;
struct fuse_in_header {int /*<<< orphan*/  nodeid; } ;
struct TYPE_3__ {int /*<<< orphan*/  mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fuse_internal_forget_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
fuse_internal_forget_callback(struct fuse_ticket *ftick, struct uio *uio)
{
	fuse_internal_forget_send(ftick->tk_data->mp, curthread, NULL,
	    ((struct fuse_in_header *)ftick->tk_ms_fiov.base)->nodeid, 1);

	return 0;
}