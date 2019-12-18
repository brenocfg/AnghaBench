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
struct iovec {int dummy; } ;
struct iov_iter {int nr_segs; int /*<<< orphan*/  iov; } ;
struct bio_map_data {int /*<<< orphan*/  iov; struct iov_iter iter; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int UIO_MAXIOV ; 
 int /*<<< orphan*/  iov ; 
 struct bio_map_data* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  struct_size (struct bio_map_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct bio_map_data *bio_alloc_map_data(struct iov_iter *data,
					       gfp_t gfp_mask)
{
	struct bio_map_data *bmd;
	if (data->nr_segs > UIO_MAXIOV)
		return NULL;

	bmd = kmalloc(struct_size(bmd, iov, data->nr_segs), gfp_mask);
	if (!bmd)
		return NULL;
	memcpy(bmd->iov, data->iov, sizeof(struct iovec) * data->nr_segs);
	bmd->iter = *data;
	bmd->iter.iov = bmd->iov;
	return bmd;
}