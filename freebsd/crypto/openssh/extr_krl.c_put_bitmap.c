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
struct bitmap {int dummy; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 size_t bitmap_nbytes (struct bitmap*) ; 
 scalar_t__ bitmap_to_string (struct bitmap*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int sshbuf_put_bignum2_bytes (struct sshbuf*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
put_bitmap(struct sshbuf *buf, struct bitmap *bitmap)
{
	size_t len;
	u_char *blob;
	int r;

	len = bitmap_nbytes(bitmap);
	if ((blob = malloc(len)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if (bitmap_to_string(bitmap, blob, len) != 0) {
		free(blob);
		return SSH_ERR_INTERNAL_ERROR;
	}
	r = sshbuf_put_bignum2_bytes(buf, blob, len);
	free(blob);
	return r;
}