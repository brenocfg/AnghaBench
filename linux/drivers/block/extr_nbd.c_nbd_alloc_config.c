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
struct nbd_config {int /*<<< orphan*/  live_connections; int /*<<< orphan*/  blksize; int /*<<< orphan*/  conn_wait; int /*<<< orphan*/  recv_wq; int /*<<< orphan*/  recv_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  NBD_DEF_BLKSIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct nbd_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nbd_config *nbd_alloc_config(void)
{
	struct nbd_config *config;

	config = kzalloc(sizeof(struct nbd_config), GFP_NOFS);
	if (!config)
		return NULL;
	atomic_set(&config->recv_threads, 0);
	init_waitqueue_head(&config->recv_wq);
	init_waitqueue_head(&config->conn_wait);
	config->blksize = NBD_DEF_BLKSIZE;
	atomic_set(&config->live_connections, 0);
	try_module_get(THIS_MODULE);
	return config;
}