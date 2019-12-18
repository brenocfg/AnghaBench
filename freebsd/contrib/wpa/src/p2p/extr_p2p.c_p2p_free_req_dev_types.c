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
struct p2p_data {int /*<<< orphan*/ * req_dev_types; scalar_t__ num_req_dev_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p2p_free_req_dev_types(struct p2p_data *p2p)
{
	p2p->num_req_dev_types = 0;
	os_free(p2p->req_dev_types);
	p2p->req_dev_types = NULL;
}