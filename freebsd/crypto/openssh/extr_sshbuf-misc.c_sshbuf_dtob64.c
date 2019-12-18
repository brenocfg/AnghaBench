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
 int SIZE_MAX ; 
 int b64_ntop (int /*<<< orphan*/  const*,size_t,char*,size_t) ; 
 int /*<<< orphan*/  explicit_bzero (char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 size_t sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/ * sshbuf_ptr (struct sshbuf*) ; 
 char* strdup (char*) ; 

char *
sshbuf_dtob64(struct sshbuf *buf)
{
	size_t len = sshbuf_len(buf), plen;
	const u_char *p = sshbuf_ptr(buf);
	char *ret;
	int r;

	if (len == 0)
		return strdup("");
	plen = ((len + 2) / 3) * 4 + 1;
	if (SIZE_MAX / 2 <= len || (ret = malloc(plen)) == NULL)
		return NULL;
	if ((r = b64_ntop(p, len, ret, plen)) == -1) {
		explicit_bzero(ret, plen);
		free(ret);
		return NULL;
	}
	return ret;
}