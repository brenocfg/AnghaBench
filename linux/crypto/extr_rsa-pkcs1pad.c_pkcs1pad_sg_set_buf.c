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
 int /*<<< orphan*/  sg_chain (struct scatterlist*,int,struct scatterlist*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,void*,size_t) ; 

__attribute__((used)) static void pkcs1pad_sg_set_buf(struct scatterlist *sg, void *buf, size_t len,
		struct scatterlist *next)
{
	int nsegs = next ? 2 : 1;

	sg_init_table(sg, nsegs);
	sg_set_buf(sg, buf, len);

	if (next)
		sg_chain(sg, nsegs, next);
}