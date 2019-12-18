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
 int stm32_hash_finup (struct ahash_request*) ; 
 scalar_t__ stm32_hash_init (struct ahash_request*) ; 

__attribute__((used)) static int stm32_hash_digest(struct ahash_request *req)
{
	return stm32_hash_init(req) ?: stm32_hash_finup(req);
}