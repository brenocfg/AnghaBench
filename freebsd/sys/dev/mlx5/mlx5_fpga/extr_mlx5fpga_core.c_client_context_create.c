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
struct mlx5_fpga_device {int /*<<< orphan*/  client_data_list; } ;
struct mlx5_fpga_client_data {int added; int /*<<< orphan*/  list; int /*<<< orphan*/ * data; struct mlx5_fpga_client* client; } ;
struct mlx5_fpga_client {int /*<<< orphan*/  (* create ) (struct mlx5_fpga_device*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5_fpga_client_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (struct mlx5_fpga_device*,char*,struct mlx5_fpga_client_data*,struct mlx5_fpga_client*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_fpga_device*) ; 

__attribute__((used)) static int client_context_create(struct mlx5_fpga_device *fdev,
				 struct mlx5_fpga_client *client,
				 struct mlx5_fpga_client_data **pctx)
{
	struct mlx5_fpga_client_data *context;

	context = kmalloc(sizeof(*context), GFP_KERNEL);
	if (!context)
		return -ENOMEM;

	context->client = client;
	context->data = NULL;
	context->added  = false;
	list_add(&context->list, &fdev->client_data_list);

	mlx5_fpga_dbg(fdev, "Adding client context %p client %p\n",
		      context, client);

	if (client->create)
		client->create(fdev);

	if (pctx)
		*pctx = context;
	return 0;
}