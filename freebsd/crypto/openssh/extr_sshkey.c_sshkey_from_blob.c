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
struct sshkey {int dummy; } ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_from (int /*<<< orphan*/  const*,size_t) ; 
 int sshkey_from_blob_internal (struct sshbuf*,struct sshkey**,int) ; 

int
sshkey_from_blob(const u_char *blob, size_t blen, struct sshkey **keyp)
{
	struct sshbuf *b;
	int r;

	if ((b = sshbuf_from(blob, blen)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	r = sshkey_from_blob_internal(b, keyp, 1);
	sshbuf_free(b);
	return r;
}