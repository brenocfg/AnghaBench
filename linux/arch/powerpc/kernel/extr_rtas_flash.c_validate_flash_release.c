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
struct rtas_validate_flash_t {scalar_t__ status; int /*<<< orphan*/  buf_size; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALIDATE_BUF_SIZE ; 
 scalar_t__ VALIDATE_READY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rtas_validate_flash_t rtas_validate_flash_data ; 
 int /*<<< orphan*/  rtas_validate_flash_mutex ; 
 int /*<<< orphan*/  validate_flash (struct rtas_validate_flash_t* const) ; 

__attribute__((used)) static int validate_flash_release(struct inode *inode, struct file *file)
{
	struct rtas_validate_flash_t *const args_buf =
		&rtas_validate_flash_data;

	mutex_lock(&rtas_validate_flash_mutex);

	if (args_buf->status == VALIDATE_READY) {
		args_buf->buf_size = VALIDATE_BUF_SIZE;
		validate_flash(args_buf);
	}

	mutex_unlock(&rtas_validate_flash_mutex);
	return 0;
}