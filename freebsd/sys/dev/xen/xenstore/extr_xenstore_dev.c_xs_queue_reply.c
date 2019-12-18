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
struct xs_dev_data {char* read_buffer; int /*<<< orphan*/  ev_rsel; int /*<<< orphan*/  read_cons; int /*<<< orphan*/  read_prod; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t MASK_READ_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct xs_dev_data*) ; 

__attribute__((used)) static void
xs_queue_reply(struct xs_dev_data *u, const char *data, unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++, u->read_prod++)
		u->read_buffer[MASK_READ_IDX(u->read_prod)] = data[i];

	KASSERT((u->read_prod - u->read_cons) <= sizeof(u->read_buffer),
	    ("xenstore reply too big"));

	wakeup(u);
	selwakeup(&u->ev_rsel);
}