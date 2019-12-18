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
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * TO_HEAD (int /*<<< orphan*/ ) ; 
 int TO_HEAD_SIZE (int /*<<< orphan*/ ) ; 
 int sg_copy_from_buffer (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sg_nents (struct scatterlist*) ; 

__attribute__((used)) static int add_comp_head(struct scatterlist *dst, u8 req_type)
{
	int head_size = TO_HEAD_SIZE(req_type);
	const u8 *head = TO_HEAD(req_type);
	int ret;

	ret = sg_copy_from_buffer(dst, sg_nents(dst), head, head_size);
	if (ret != head_size)
		return -ENOMEM;

	return head_size;
}