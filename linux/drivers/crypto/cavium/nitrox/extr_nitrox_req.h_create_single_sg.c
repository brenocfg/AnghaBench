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
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,void*,int) ; 

__attribute__((used)) static inline struct scatterlist *create_single_sg(struct scatterlist *sg,
						   void *buf, int buflen)
{
	sg_set_buf(sg, buf, buflen);
	sg++;
	return sg;
}