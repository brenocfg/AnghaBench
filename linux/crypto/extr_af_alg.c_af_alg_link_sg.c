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
struct af_alg_sgl {scalar_t__ sg; scalar_t__ npages; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_chain (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sg_unmark_end (scalar_t__) ; 

__attribute__((used)) static void af_alg_link_sg(struct af_alg_sgl *sgl_prev,
			   struct af_alg_sgl *sgl_new)
{
	sg_unmark_end(sgl_prev->sg + sgl_prev->npages - 1);
	sg_chain(sgl_prev->sg, sgl_prev->npages + 1, sgl_new->sg);
}