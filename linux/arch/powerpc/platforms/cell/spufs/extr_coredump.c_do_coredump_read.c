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
typedef  int /*<<< orphan*/  u64 ;
struct spu_context {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {size_t (* read ) (struct spu_context*,void*,size_t,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get ) (struct spu_context*) ;} ;

/* Variables and functions */
 int snprintf (void*,size_t,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* spufs_coredump_read ; 
 size_t stub1 (struct spu_context*,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct spu_context*) ; 

__attribute__((used)) static ssize_t do_coredump_read(int num, struct spu_context *ctx, void *buffer,
				size_t size, loff_t *off)
{
	u64 data;
	int ret;

	if (spufs_coredump_read[num].read)
		return spufs_coredump_read[num].read(ctx, buffer, size, off);

	data = spufs_coredump_read[num].get(ctx);
	ret = snprintf(buffer, size, "0x%.16llx", data);
	if (ret >= size)
		return size;
	return ++ret; /* count trailing NULL */
}