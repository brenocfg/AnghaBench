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
struct se_crypto_request {int /*<<< orphan*/  gfp; } ;
struct nitrox_kcrypt_request {int /*<<< orphan*/  dst; struct se_crypto_request creq; } ;

/* Variables and functions */
 int COMP_HLEN ; 
 int ENOMEM ; 
 int ORH_HLEN ; 
 int /*<<< orphan*/  alloc_req_buf (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int alloc_dst_req_buf(struct nitrox_kcrypt_request *nkreq,
				    int nents)
{
	int extralen = ORH_HLEN + COMP_HLEN;
	struct se_crypto_request *creq = &nkreq->creq;

	nkreq->dst = alloc_req_buf(nents, extralen, creq->gfp);
	if (!nkreq->dst)
		return -ENOMEM;

	return 0;
}