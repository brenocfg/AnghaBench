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
struct msg_write {int dummy; } ;
struct msg_hdr {int len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_WRITE ; 
 void* _recv (int,void*,size_t) ; 
 size_t bytes ; 
 int errno ; 
 scalar_t__ fd ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 void* file_addr ; 
 int ftruncate (scalar_t__,size_t) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_send_resp (int,struct msg_hdr*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int server_write(int rs, struct msg_hdr *msg)
{
	size_t len;
	int ret;

	printf("transferring");
	fflush(NULL);
	if (fd <= 0) {
		printf("...file not opened\n");
		ret = EINVAL;
		goto out;
	}

	if (msg->len != sizeof(struct msg_write)) {
		printf("...invalid message length %d\n", msg->len);
		ret = EINVAL;
		goto out;
	}

	ret = _recv(rs, (char *) &bytes, sizeof bytes);
	if (ret != sizeof bytes)
		goto out;

	ret = ftruncate(fd, bytes);
	if (ret)
		goto out;

	file_addr = mmap(NULL, bytes, PROT_WRITE, MAP_SHARED, fd, 0);
	if (file_addr == (void *) -1) {
		printf("...error mapping file\n");
		ret = errno;
		goto out;
	}

	printf("...%lld bytes...", (long long) bytes);
	fflush(NULL);
	len = _recv(rs, file_addr, bytes);
	if (len != bytes) {
		printf("...error receiving data\n");
		ret = (int) len;
	}
out:
	msg_send_resp(rs, msg, ret);
	return ret;
}