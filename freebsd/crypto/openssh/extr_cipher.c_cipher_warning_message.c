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
struct sshcipher_ctx {int /*<<< orphan*/ * cipher; } ;

/* Variables and functions */

const char *
cipher_warning_message(const struct sshcipher_ctx *cc)
{
	if (cc == NULL || cc->cipher == NULL)
		return NULL;
	/* XXX repurpose for CBC warning */
	return NULL;
}