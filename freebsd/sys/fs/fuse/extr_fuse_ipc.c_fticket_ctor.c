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
struct fuse_ticket {scalar_t__ tk_unique; int /*<<< orphan*/  tk_refcount; scalar_t__ irq_unique; struct fuse_data* tk_data; } ;
struct fuse_data {int /*<<< orphan*/  ticketer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ASSERT_AW_DONE (struct fuse_ticket*) ; 
 int /*<<< orphan*/  FUSE_ASSERT_MS_DONE (struct fuse_ticket*) ; 
 void* atomic_fetchadd_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fticket_refresh (struct fuse_ticket*) ; 
 int /*<<< orphan*/  fuse_ticket_count ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
fticket_ctor(void *mem, int size, void *arg, int flags)
{
	struct fuse_ticket *ftick = mem;
	struct fuse_data *data = arg;

	FUSE_ASSERT_MS_DONE(ftick);
	FUSE_ASSERT_AW_DONE(ftick);

	ftick->tk_data = data;

	if (ftick->tk_unique != 0)
		fticket_refresh(ftick);

	/* May be truncated to 32 bits */
	ftick->tk_unique = atomic_fetchadd_long(&data->ticketer, 1);
	if (ftick->tk_unique == 0)
		ftick->tk_unique = atomic_fetchadd_long(&data->ticketer, 1);

	ftick->irq_unique = 0;

	refcount_init(&ftick->tk_refcount, 1);
	counter_u64_add(fuse_ticket_count, 1);

	return 0;
}