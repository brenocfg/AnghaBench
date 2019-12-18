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
struct opal_prd_msg_header {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct opal_prd_msg {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_PRD_MSG_TYPE_FINI ; 
 int /*<<< orphan*/  atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  opal_prd_msg (struct opal_prd_msg*) ; 
 int /*<<< orphan*/  prd_usage ; 

__attribute__((used)) static int opal_prd_release(struct inode *inode, struct file *file)
{
	struct opal_prd_msg_header msg;

	msg.size = cpu_to_be16(sizeof(msg));
	msg.type = OPAL_PRD_MSG_TYPE_FINI;

	opal_prd_msg((struct opal_prd_msg *)&msg);

	atomic_xchg(&prd_usage, 0);

	return 0;
}