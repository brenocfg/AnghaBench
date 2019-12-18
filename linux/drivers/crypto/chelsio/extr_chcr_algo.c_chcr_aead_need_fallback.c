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
struct aead_request {unsigned int cryptlen; int assoclen; } ;

/* Variables and functions */
 int MAX_DSGL_ENT ; 
 int SGE_MAX_WR_LEN ; 
 unsigned int crypto_aead_authsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 

__attribute__((used)) static int chcr_aead_need_fallback(struct aead_request *req, int dst_nents,
				   int aadmax, int wrlen,
				   unsigned short op_type)
{
	unsigned int authsize = crypto_aead_authsize(crypto_aead_reqtfm(req));

	if (((req->cryptlen - (op_type ? authsize : 0)) == 0) ||
	    dst_nents > MAX_DSGL_ENT ||
	    (req->assoclen > aadmax) ||
	    (wrlen > SGE_MAX_WR_LEN))
		return 1;
	return 0;
}