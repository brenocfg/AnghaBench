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
struct ahash_request {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int ahash_final (struct ahash_request*) ; 
 int /*<<< orphan*/  flow_log (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_hmac_final(struct ahash_request *req)
{
	flow_log("ahash_hmac_final() nbytes:%u\n", req->nbytes);

	return ahash_final(req);
}