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
struct sshkey {int dummy; } ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int sshkey_format_text (struct sshkey const*,struct sshbuf*) ; 

int
sshkey_write(const struct sshkey *key, FILE *f)
{
	struct sshbuf *b = NULL;
	int r = SSH_ERR_INTERNAL_ERROR;

	if ((b = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshkey_format_text(key, b)) != 0)
		goto out;
	if (fwrite(sshbuf_ptr(b), sshbuf_len(b), 1, f) != 1) {
		if (feof(f))
			errno = EPIPE;
		r = SSH_ERR_SYSTEM_ERROR;
		goto out;
	}
	/* Success */
	r = 0;
 out:
	sshbuf_free(b);
	return r;
}