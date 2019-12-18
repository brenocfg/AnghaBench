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
 int cryptd_hash_enqueue (struct ahash_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cryptd_hash_final ; 

__attribute__((used)) static int cryptd_hash_final_enqueue(struct ahash_request *req)
{
	return cryptd_hash_enqueue(req, cryptd_hash_final);
}