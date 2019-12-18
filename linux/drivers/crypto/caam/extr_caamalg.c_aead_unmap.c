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
struct device {int dummy; } ;
struct aead_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct aead_edesc {int /*<<< orphan*/  sec4_sg_bytes; int /*<<< orphan*/  sec4_sg_dma; int /*<<< orphan*/  dst_nents; int /*<<< orphan*/  src_nents; } ;

/* Variables and functions */
 int /*<<< orphan*/  caam_unmap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aead_unmap(struct device *dev,
		       struct aead_edesc *edesc,
		       struct aead_request *req)
{
	caam_unmap(dev, req->src, req->dst,
		   edesc->src_nents, edesc->dst_nents, 0, 0,
		   edesc->sec4_sg_dma, edesc->sec4_sg_bytes);
}