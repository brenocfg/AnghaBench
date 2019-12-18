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
struct stm32_hash_dev {int /*<<< orphan*/  engine; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int crypto_transfer_hash_request_to_engine (int /*<<< orphan*/ ,struct ahash_request*) ; 

__attribute__((used)) static int stm32_hash_handle_queue(struct stm32_hash_dev *hdev,
				   struct ahash_request *req)
{
	return crypto_transfer_hash_request_to_engine(hdev->engine, req);
}