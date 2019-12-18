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
struct se_crypto_request {struct scatterlist* src; } ;
struct scatterlist {int dummy; } ;
struct nitrox_kcrypt_request {char* src; struct se_crypto_request creq; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_multi_sg (struct scatterlist*,struct scatterlist*,int) ; 
 struct scatterlist* create_single_sg (struct scatterlist*,char*,int) ; 
 struct scatterlist* nitrox_creq_src_sg (char*,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 

__attribute__((used)) static inline void nitrox_creq_set_src_sg(struct nitrox_kcrypt_request *nkreq,
					  int nents, int ivsize,
					  struct scatterlist *src, int buflen)
{
	char *iv = nkreq->src;
	struct scatterlist *sg;
	struct se_crypto_request *creq = &nkreq->creq;

	creq->src = nitrox_creq_src_sg(iv, ivsize);
	sg = creq->src;
	sg_init_table(sg, nents);

	/* Input format:
	 * +----+----------------+
	 * | IV | SRC sg entries |
	 * +----+----------------+
	 */

	/* IV */
	sg = create_single_sg(sg, iv, ivsize);
	/* SRC entries */
	create_multi_sg(sg, src, buflen);
}