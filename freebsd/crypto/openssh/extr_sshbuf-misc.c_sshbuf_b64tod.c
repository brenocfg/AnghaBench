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
 int SSH_ERR_INVALID_FORMAT ; 
 int b64_pton (char const*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int sshbuf_put (struct sshbuf*,int /*<<< orphan*/ *,int) ; 
 size_t strlen (char const*) ; 

int
sshbuf_b64tod(struct sshbuf *buf, const char *b64)
{
	size_t plen = strlen(b64);
	int nlen, r;
	u_char *p;

	if (plen == 0)
		return 0;
	if ((p = malloc(plen)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((nlen = b64_pton(b64, p, plen)) < 0) {
		explicit_bzero(p, plen);
		free(p);
		return SSH_ERR_INVALID_FORMAT;
	}
	if ((r = sshbuf_put(buf, p, nlen)) < 0) {
		explicit_bzero(p, plen);
		free(p);
		return r;
	}
	explicit_bzero(p, plen);
	free(p);
	return 0;
}