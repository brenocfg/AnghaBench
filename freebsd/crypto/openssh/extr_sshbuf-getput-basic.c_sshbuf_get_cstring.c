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
 int /*<<< orphan*/  SSHBUF_DBG (char*) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_FORMAT ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/  const*,char,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 
 int sshbuf_peek_string_direct (struct sshbuf*,int /*<<< orphan*/  const**,size_t*) ; 
 int sshbuf_skip_string (struct sshbuf*) ; 

int
sshbuf_get_cstring(struct sshbuf *buf, char **valp, size_t *lenp)
{
	size_t len;
	const u_char *p, *z;
	int r;

	if (valp != NULL)
		*valp = NULL;
	if (lenp != NULL)
		*lenp = 0;
	if ((r = sshbuf_peek_string_direct(buf, &p, &len)) != 0)
		return r;
	/* Allow a \0 only at the end of the string */
	if (len > 0 &&
	    (z = memchr(p , '\0', len)) != NULL && z < p + len - 1) {
		SSHBUF_DBG(("SSH_ERR_INVALID_FORMAT"));
		return SSH_ERR_INVALID_FORMAT;
	}
	if ((r = sshbuf_skip_string(buf)) != 0)
		return -1;
	if (valp != NULL) {
		if ((*valp = malloc(len + 1)) == NULL) {
			SSHBUF_DBG(("SSH_ERR_ALLOC_FAIL"));
			return SSH_ERR_ALLOC_FAIL;
		}
		if (len != 0)
			memcpy(*valp, p, len);
		(*valp)[len] = '\0';
	}
	if (lenp != NULL)
		*lenp = (size_t)len;
	return 0;
}