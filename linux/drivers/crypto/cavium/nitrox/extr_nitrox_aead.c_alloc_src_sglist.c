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
struct nitrox_kcrypt_request {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int alloc_src_req_buf (struct nitrox_kcrypt_request*,int,int) ; 
 int /*<<< orphan*/  nitrox_creq_copy_iv (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nitrox_creq_set_src_sg (struct nitrox_kcrypt_request*,int,int,struct scatterlist*,int) ; 
 int sg_nents_for_len (struct scatterlist*,int) ; 

__attribute__((used)) static int alloc_src_sglist(struct nitrox_kcrypt_request *nkreq,
			    struct scatterlist *src, char *iv, int ivsize,
			    int buflen)
{
	int nents = sg_nents_for_len(src, buflen);
	int ret;

	if (nents < 0)
		return nents;

	/* IV entry */
	nents += 1;
	/* Allocate buffer to hold IV and input scatterlist array */
	ret = alloc_src_req_buf(nkreq, nents, ivsize);
	if (ret)
		return ret;

	nitrox_creq_copy_iv(nkreq->src, iv, ivsize);
	nitrox_creq_set_src_sg(nkreq, nents, ivsize, src, buflen);

	return 0;
}