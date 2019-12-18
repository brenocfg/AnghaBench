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
struct hypfs_dbfs_data {int /*<<< orphan*/  buf_free_ptr; TYPE_1__* dbfs_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* data_free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hypfs_dbfs_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hypfs_dbfs_data_free(struct hypfs_dbfs_data *data)
{
	data->dbfs_file->data_free(data->buf_free_ptr);
	kfree(data);
}