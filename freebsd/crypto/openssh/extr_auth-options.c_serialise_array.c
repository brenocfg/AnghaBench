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

/* Variables and functions */
 size_t INT_MAX ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put_cstring (struct sshbuf*,char*) ; 
 int sshbuf_put_stringb (struct sshbuf*,struct sshbuf*) ; 
 int sshbuf_put_u32 (struct sshbuf*,size_t) ; 

__attribute__((used)) static int
serialise_array(struct sshbuf *m, char **a, size_t n)
{
	struct sshbuf *b;
	size_t i;
	int r;

	if (n > INT_MAX)
		return SSH_ERR_INTERNAL_ERROR;

	if ((b = sshbuf_new()) == NULL) {
		return SSH_ERR_ALLOC_FAIL;
	}
	for (i = 0; i < n; i++) {
		if ((r = sshbuf_put_cstring(b, a[i])) != 0) {
			sshbuf_free(b);
			return r;
		}
	}
	if ((r = sshbuf_put_u32(m, n)) != 0 ||
	    (r = sshbuf_put_stringb(m, b)) != 0) {
		sshbuf_free(b);
		return r;
	}
	/* success */
	return 0;
}