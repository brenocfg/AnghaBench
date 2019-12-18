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

/* Variables and functions */
 int /*<<< orphan*/  ERR_peek_error () ; 
 int /*<<< orphan*/  ERR_peek_last_error () ; 
 scalar_t__ SSH_ERR_KEY_WRONG_PASSPHRASE ; 
 int translate_libcrypto_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
convert_libcrypto_error(void)
{
	/*
	 * Some password errors are reported at the beginning
	 * of the error queue.
	 */
	if (translate_libcrypto_error(ERR_peek_error()) ==
	    SSH_ERR_KEY_WRONG_PASSPHRASE)
		return SSH_ERR_KEY_WRONG_PASSPHRASE;
	return translate_libcrypto_error(ERR_peek_last_error());
}