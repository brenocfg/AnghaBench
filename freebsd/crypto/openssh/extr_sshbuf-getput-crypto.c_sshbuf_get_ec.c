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
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  SSHBUF_ABORT () ; 
 int /*<<< orphan*/  SSHBUF_DBG (char*) ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int get_ec (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ sshbuf_get_string_direct (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sshbuf_peek_string_direct (struct sshbuf*,int /*<<< orphan*/  const**,size_t*) ; 

int
sshbuf_get_ec(struct sshbuf *buf, EC_POINT *v, const EC_GROUP *g)
{
	const u_char *d;
	size_t len;
	int r;

	if ((r = sshbuf_peek_string_direct(buf, &d, &len)) < 0)
		return r;
	if ((r = get_ec(d, len, v, g)) != 0)
		return r;
	/* Skip string */
	if (sshbuf_get_string_direct(buf, NULL, NULL) != 0) {
		/* Shouldn't happen */
		SSHBUF_DBG(("SSH_ERR_INTERNAL_ERROR"));
		SSHBUF_ABORT();
		return SSH_ERR_INTERNAL_ERROR;
	}
	return 0;
}