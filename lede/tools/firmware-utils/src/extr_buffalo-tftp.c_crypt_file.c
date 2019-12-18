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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  crypt_header (unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypt_key1 ; 
 int /*<<< orphan*/  crypt_key2 ; 
 scalar_t__ do_decrypt ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ get_file_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifname ; 
 unsigned char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  ofname ; 
 int read_file_to_buf (int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 
 int write_buf_to_file (int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 

__attribute__((used)) static int crypt_file(void)
{
	unsigned char *buf = NULL;
	ssize_t src_len;
	int err;
	int ret = -1;

	src_len = get_file_size(ifname);
	if (src_len < 0) {
		ERR("unable to get size of '%s'", ifname);
		goto out;
	}

	buf = malloc(src_len);
	if (buf == NULL) {
		ERR("no memory for the buffer");
		goto out;
	}

	err = read_file_to_buf(ifname, buf, src_len);
	if (err) {
		ERR("unable to read from file '%s'", ifname);
		goto out;
	}

	if (do_decrypt)
		crypt_header(buf, 512, crypt_key2, crypt_key1);
	else
		crypt_header(buf, 512, crypt_key1, crypt_key2);

	err = write_buf_to_file(ofname, buf, src_len);
	if (err) {
		ERR("unable to write to file '%s'", ofname);
		goto out;
	}

	ret = 0;

out:
	free(buf);
	return ret;
}