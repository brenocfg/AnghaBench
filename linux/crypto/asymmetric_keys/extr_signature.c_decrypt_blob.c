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
struct kernel_pkey_params {int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int asymmetric_key_eds_op (struct kernel_pkey_params*,void const*,void*) ; 
 int /*<<< orphan*/  kernel_pkey_decrypt ; 

int decrypt_blob(struct kernel_pkey_params *params,
		 const void *enc, void *data)
{
	params->op = kernel_pkey_decrypt;
	return asymmetric_key_eds_op(params, enc, data);
}