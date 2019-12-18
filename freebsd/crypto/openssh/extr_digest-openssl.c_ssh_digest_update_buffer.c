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
struct sshbuf {int dummy; } ;
struct ssh_digest_ctx {int dummy; } ;

/* Variables and functions */
 int ssh_digest_update (struct ssh_digest_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf const*) ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf const*) ; 

int
ssh_digest_update_buffer(struct ssh_digest_ctx *ctx, const struct sshbuf *b)
{
	return ssh_digest_update(ctx, sshbuf_ptr(b), sshbuf_len(b));
}