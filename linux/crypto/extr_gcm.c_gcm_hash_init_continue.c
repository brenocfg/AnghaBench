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
typedef  int /*<<< orphan*/  u32 ;
struct aead_request {scalar_t__ assoclen; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int gcm_hash_assoc_continue (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcm_hash_assoc_done ; 
 int gcm_hash_assoc_remain_continue (struct aead_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ gcm_hash_update (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gcm_hash_init_continue(struct aead_request *req, u32 flags)
{
	if (req->assoclen)
		return gcm_hash_update(req, gcm_hash_assoc_done,
				       req->src, req->assoclen, flags) ?:
		       gcm_hash_assoc_continue(req, flags);

	return gcm_hash_assoc_remain_continue(req, flags);
}