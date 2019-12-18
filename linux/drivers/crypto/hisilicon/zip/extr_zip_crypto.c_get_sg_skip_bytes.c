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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPLIT_NUM ; 
 int sg_split (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*,struct scatterlist**,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_sg_skip_bytes(struct scatterlist *sgl, size_t bytes,
			     size_t remains, struct scatterlist **out)
{
#define SPLIT_NUM 2
	size_t split_sizes[SPLIT_NUM];
	int out_mapped_nents[SPLIT_NUM];

	split_sizes[0] = bytes;
	split_sizes[1] = remains;

	return sg_split(sgl, 0, 0, SPLIT_NUM, split_sizes, out,
			out_mapped_nents, GFP_KERNEL);
}