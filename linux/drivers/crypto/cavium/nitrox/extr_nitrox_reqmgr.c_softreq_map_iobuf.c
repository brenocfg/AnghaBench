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
struct se_crypto_request {int dummy; } ;
struct nitrox_softreq {int dummy; } ;

/* Variables and functions */
 int dma_map_inbufs (struct nitrox_softreq*,struct se_crypto_request*) ; 
 int dma_map_outbufs (struct nitrox_softreq*,struct se_crypto_request*) ; 
 int /*<<< orphan*/  softreq_unmap_sgbufs (struct nitrox_softreq*) ; 

__attribute__((used)) static inline int softreq_map_iobuf(struct nitrox_softreq *sr,
				    struct se_crypto_request *creq)
{
	int ret;

	ret = dma_map_inbufs(sr, creq);
	if (ret)
		return ret;

	ret = dma_map_outbufs(sr, creq);
	if (ret)
		softreq_unmap_sgbufs(sr);

	return ret;
}