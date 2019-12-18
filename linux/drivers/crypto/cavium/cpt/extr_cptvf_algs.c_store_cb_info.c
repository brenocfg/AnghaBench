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
struct cpt_request_info {void* callback_arg; void* callback; } ;
struct ablkcipher_request {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ cvm_callback ; 

__attribute__((used)) static inline void store_cb_info(struct ablkcipher_request *req,
				 struct cpt_request_info *req_info)
{
	req_info->callback = (void *)cvm_callback;
	req_info->callback_arg = (void *)&req->base;
}