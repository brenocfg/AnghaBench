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
typedef  int /*<<< orphan*/  SHA256_CTX ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha256_hash (unsigned char*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
sha256_fd(int fd, char out[SHA256_DIGEST_LENGTH * 2 + 1])
{
	int my_fd;
	FILE *fp;
	char buffer[BUFSIZ];
	unsigned char hash[SHA256_DIGEST_LENGTH];
	size_t r;
	int ret;
	SHA256_CTX sha256;

	my_fd = -1;
	fp = NULL;
	r = 0;
	ret = 1;

	out[0] = '\0';

	/* Duplicate the fd so that fclose(3) does not close it. */
	if ((my_fd = dup(fd)) == -1) {
		warnx("dup");
		goto cleanup;
	}

	if ((fp = fdopen(my_fd, "rb")) == NULL) {
		warnx("fdopen");
		goto cleanup;
	}

	SHA256_Init(&sha256);

	while ((r = fread(buffer, 1, BUFSIZ, fp)) > 0)
		SHA256_Update(&sha256, buffer, r);

	if (ferror(fp) != 0) {
		warnx("fread");
		goto cleanup;
	}

	SHA256_Final(hash, &sha256);
	sha256_hash(hash, out);
	ret = 0;

cleanup:
	if (fp != NULL)
		fclose(fp);
	else if (my_fd != -1)
		close(my_fd);
	(void)lseek(fd, 0, SEEK_SET);

	return (ret);
}