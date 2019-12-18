#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct testvec_config {TYPE_2__* src_divs; TYPE_2__* dst_divs; scalar_t__ inplace; } ;
struct kvec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; int /*<<< orphan*/  sgl_ptr; } ;
struct cipher_test_sglists {TYPE_1__ dst; TYPE_1__ src; } ;
struct TYPE_4__ {scalar_t__ proportion_of_total; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 int build_test_sglist (TYPE_1__*,TYPE_2__*,unsigned int,unsigned int,struct iov_iter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec const*,unsigned int,unsigned int) ; 
 unsigned int max (unsigned int,unsigned int) ; 

__attribute__((used)) static int build_cipher_test_sglists(struct cipher_test_sglists *tsgls,
				     const struct testvec_config *cfg,
				     unsigned int alignmask,
				     unsigned int src_total_len,
				     unsigned int dst_total_len,
				     const struct kvec *inputs,
				     unsigned int nr_inputs)
{
	struct iov_iter input;
	int err;

	iov_iter_kvec(&input, WRITE, inputs, nr_inputs, src_total_len);
	err = build_test_sglist(&tsgls->src, cfg->src_divs, alignmask,
				cfg->inplace ?
					max(dst_total_len, src_total_len) :
					src_total_len,
				&input, NULL);
	if (err)
		return err;

	if (cfg->inplace) {
		tsgls->dst.sgl_ptr = tsgls->src.sgl;
		tsgls->dst.nents = tsgls->src.nents;
		return 0;
	}
	return build_test_sglist(&tsgls->dst,
				 cfg->dst_divs[0].proportion_of_total ?
					cfg->dst_divs : cfg->src_divs,
				 alignmask, dst_total_len, NULL, NULL);
}