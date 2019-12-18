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
typedef  int u_int ;
typedef  int /*<<< orphan*/  DSA ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_generate_parameters_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_KEY_LENGTH ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 

__attribute__((used)) static int
dsa_generate_private_key(u_int bits, DSA **dsap)
{
	DSA *private;
	int ret = SSH_ERR_INTERNAL_ERROR;

	if (dsap == NULL)
		return SSH_ERR_INVALID_ARGUMENT;
	if (bits != 1024)
		return SSH_ERR_KEY_LENGTH;
	if ((private = DSA_new()) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	*dsap = NULL;
	if (!DSA_generate_parameters_ex(private, bits, NULL, 0, NULL,
	    NULL, NULL) || !DSA_generate_key(private)) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	*dsap = private;
	private = NULL;
	ret = 0;
 out:
	DSA_free(private);
	return ret;
}