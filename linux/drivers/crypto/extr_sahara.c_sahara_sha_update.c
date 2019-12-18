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
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int sahara_sha_enqueue (struct ahash_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sahara_sha_update(struct ahash_request *req)
{
	return sahara_sha_enqueue(req, 0);
}