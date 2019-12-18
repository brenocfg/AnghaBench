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
typedef  int /*<<< orphan*/  u_int ;
struct sshcipher_ctx {int /*<<< orphan*/  plaintext; } ;

/* Variables and functions */

u_int
cipher_ctx_is_plaintext(struct sshcipher_ctx *cc)
{
	return cc->plaintext;
}