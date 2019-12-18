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
struct tools_context {int /*<<< orphan*/  access_type; int /*<<< orphan*/  tdev; } ;
struct thread {int dummy; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FPGA_ACCESS_TYPE_DONTCARE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (struct tools_context*,int /*<<< orphan*/ ) ; 
 struct tools_context* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tools_char_ctx_dtor ; 

__attribute__((used)) static int
tools_char_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct tools_context *context;

	context = malloc(sizeof(*context), M_DEVBUF, M_WAITOK);
	context->tdev = dev->si_drv1;
	context->access_type = MLX5_FPGA_ACCESS_TYPE_DONTCARE;
	devfs_set_cdevpriv(context, tools_char_ctx_dtor);
	return (0);
}