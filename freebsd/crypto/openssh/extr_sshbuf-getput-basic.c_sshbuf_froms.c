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

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int sshbuf_consume (struct sshbuf*,size_t) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_from (int /*<<< orphan*/  const*,size_t) ; 
 int sshbuf_peek_string_direct (struct sshbuf*,int /*<<< orphan*/  const**,size_t*) ; 
 int sshbuf_set_parent (struct sshbuf*,struct sshbuf*) ; 

int
sshbuf_froms(struct sshbuf *buf, struct sshbuf **bufp)
{
	const u_char *p;
	size_t len;
	struct sshbuf *ret;
	int r;

	if (buf == NULL || bufp == NULL)
		return SSH_ERR_INVALID_ARGUMENT;
	*bufp = NULL;
	if ((r = sshbuf_peek_string_direct(buf, &p, &len)) != 0)
		return r;
	if ((ret = sshbuf_from(p, len)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshbuf_consume(buf, len + 4)) != 0 ||  /* Shouldn't happen */
	    (r = sshbuf_set_parent(ret, buf)) != 0) {
		sshbuf_free(ret);
		return r;
	}
	*bufp = ret;
	return 0;
}