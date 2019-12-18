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
struct rchap {int /*<<< orphan*/  rchap_challenge_len; int /*<<< orphan*/  rchap_challenge; int /*<<< orphan*/  rchap_secret; int /*<<< orphan*/  rchap_id; } ;

/* Variables and functions */
 size_t CHAP_DIGEST_LEN ; 
 void* calloc (size_t,int) ; 
 int /*<<< orphan*/  chap_compute_md5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

__attribute__((used)) static void
rchap_get_response_bin(struct rchap *rchap,
    void **responsep, size_t *response_lenp)
{
	void *response_bin;
	size_t response_bin_len = CHAP_DIGEST_LEN;

	response_bin = calloc(response_bin_len, 1);
	if (response_bin == NULL)
		log_err(1, "calloc");

	chap_compute_md5(rchap->rchap_id, rchap->rchap_secret,
	    rchap->rchap_challenge, rchap->rchap_challenge_len,
	    response_bin, response_bin_len);

	*responsep = response_bin;
	*response_lenp = response_bin_len;
}