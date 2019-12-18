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
struct nitrox_kcrypt_request {int dummy; } ;

/* Variables and functions */
 int alloc_dst_req_buf (struct nitrox_kcrypt_request*,int) ; 
 int /*<<< orphan*/  nitrox_creq_set_comp (struct nitrox_kcrypt_request*) ; 
 int /*<<< orphan*/  nitrox_creq_set_dst_sg (struct nitrox_kcrypt_request*,int,int,struct scatterlist*,int) ; 
 int /*<<< orphan*/  nitrox_creq_set_orh (struct nitrox_kcrypt_request*) ; 
 int sg_nents_for_len (struct scatterlist*,int) ; 

__attribute__((used)) static int alloc_dst_sglist(struct nitrox_kcrypt_request *nkreq,
			    struct scatterlist *dst, int ivsize, int buflen)
{
	int nents = sg_nents_for_len(dst, buflen);
	int ret;

	if (nents < 0)
		return nents;

	/* IV, ORH, COMPLETION entries */
	nents += 3;
	/* Allocate buffer to hold ORH, COMPLETION and output scatterlist
	 * array
	 */
	ret = alloc_dst_req_buf(nkreq, nents);
	if (ret)
		return ret;

	nitrox_creq_set_orh(nkreq);
	nitrox_creq_set_comp(nkreq);
	nitrox_creq_set_dst_sg(nkreq, nents, ivsize, dst, buflen);

	return 0;
}