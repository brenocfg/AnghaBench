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
struct rchap {unsigned char rchap_id; size_t rchap_challenge_len; int /*<<< orphan*/ * rchap_challenge; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void
rchap_receive_bin(struct rchap *rchap, const unsigned char id,
    const void *challenge, size_t challenge_len)
{

	rchap->rchap_id = id;
	rchap->rchap_challenge = calloc(challenge_len, 1);
	if (rchap->rchap_challenge == NULL)
		log_err(1, "calloc");
	memcpy(rchap->rchap_challenge, challenge, challenge_len);
	rchap->rchap_challenge_len = challenge_len;
}