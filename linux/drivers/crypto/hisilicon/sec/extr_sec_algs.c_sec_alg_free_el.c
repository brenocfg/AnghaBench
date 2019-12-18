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
struct sec_request_el {struct sec_request_el* sgl_out; struct sec_request_el* sgl_in; int /*<<< orphan*/  dma_in; int /*<<< orphan*/  in; int /*<<< orphan*/  dma_out; int /*<<< orphan*/  out; } ;
struct sec_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sec_request_el*) ; 
 int /*<<< orphan*/  sec_free_hw_sgl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sec_dev_info*) ; 

__attribute__((used)) static void sec_alg_free_el(struct sec_request_el *el,
			    struct sec_dev_info *info)
{
	sec_free_hw_sgl(el->out, el->dma_out, info);
	sec_free_hw_sgl(el->in, el->dma_in, info);
	kfree(el->sgl_in);
	kfree(el->sgl_out);
	kfree(el);
}