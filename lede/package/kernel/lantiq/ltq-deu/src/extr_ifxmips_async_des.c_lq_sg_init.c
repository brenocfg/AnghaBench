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
struct page {int dummy; } ;
struct des_container {char* src_buf; char* dst_buf; } ;

/* Variables and functions */
 struct page* sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void lq_sg_init(struct des_container *des_con, struct scatterlist *src,
                       struct scatterlist *dst)
{
    struct page *dst_page, *src_page;

    src_page = sg_virt(src);
    des_con->src_buf = (char *) src_page;

    dst_page = sg_virt(dst);
    des_con->dst_buf = (char *) dst_page;
}