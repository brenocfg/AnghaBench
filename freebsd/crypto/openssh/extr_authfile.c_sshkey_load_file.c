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
struct stat {int st_mode; scalar_t__ st_size; } ;
struct sshbuf {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EPIPE ; 
 scalar_t__ MAX_KEY_FILE_SIZE ; 
 int SSH_ERR_FILE_CHANGED ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 int S_IFCHR ; 
 int S_IFIFO ; 
 int S_IFSOCK ; 
 size_t atomicio (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  read ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 int sshbuf_put (struct sshbuf*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sshbuf_reset (struct sshbuf*) ; 

int
sshkey_load_file(int fd, struct sshbuf *blob)
{
	u_char buf[1024];
	size_t len;
	struct stat st;
	int r;

	if (fstat(fd, &st) < 0)
		return SSH_ERR_SYSTEM_ERROR;
	if ((st.st_mode & (S_IFSOCK|S_IFCHR|S_IFIFO)) == 0 &&
	    st.st_size > MAX_KEY_FILE_SIZE)
		return SSH_ERR_INVALID_FORMAT;
	for (;;) {
		if ((len = atomicio(read, fd, buf, sizeof(buf))) == 0) {
			if (errno == EPIPE)
				break;
			r = SSH_ERR_SYSTEM_ERROR;
			goto out;
		}
		if ((r = sshbuf_put(blob, buf, len)) != 0)
			goto out;
		if (sshbuf_len(blob) > MAX_KEY_FILE_SIZE) {
			r = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
	}
	if ((st.st_mode & (S_IFSOCK|S_IFCHR|S_IFIFO)) == 0 &&
	    st.st_size != (off_t)sshbuf_len(blob)) {
		r = SSH_ERR_FILE_CHANGED;
		goto out;
	}
	r = 0;

 out:
	explicit_bzero(buf, sizeof(buf));
	if (r != 0)
		sshbuf_reset(blob);
	return r;
}