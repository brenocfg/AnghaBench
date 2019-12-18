#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct stat {scalar_t__ st_mode; scalar_t__ st_size; } ;
struct TYPE_2__ {int len; int data; int /*<<< orphan*/  command; } ;
struct msg_open {TYPE_1__ hdr; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_OPEN ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ bytes ; 
 struct msg_open* calloc (int,int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  dst_file ; 
 int errno ; 
 scalar_t__ fd ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 void* file_addr ; 
 int /*<<< orphan*/  free (struct msg_open*) ; 
 int fstat (scalar_t__,struct stat*) ; 
 void* mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int msg_get_resp (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,scalar_t__) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rsend (int,struct msg_open*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_file ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_open(int rs)
{
	struct msg_open *msg;
	struct stat stats;
	uint32_t len;
	int ret;

	printf("opening...");
	fflush(NULL);
	fd = open(src_file, O_RDONLY);
	if (fd < 0)
		return fd;

	ret = fstat(fd, &stats);
	if (ret < 0)
		goto err1;

	bytes = (uint64_t) stats.st_size;
	file_addr = mmap(NULL, bytes, PROT_READ, MAP_SHARED, fd, 0);
	if (file_addr == (void *) -1) {
		ret = errno;
		goto err1;
	}

	len = (((uint32_t) strlen(dst_file)) + 8) & 0xFFFFFFF8;
	msg = calloc(1, sizeof(*msg) + len);
	if (!msg) {
		ret = -1;
		goto err2;
	}

	msg->hdr.command = CMD_OPEN;
	msg->hdr.len = sizeof(*msg) + len;
	msg->hdr.data = (uint32_t) stats.st_mode;
	strcpy(msg->path, dst_file);
	ret = rsend(rs, msg, msg->hdr.len, 0);
	if (ret != msg->hdr.len)
		goto err3;

	ret = msg_get_resp(rs, &msg->hdr, CMD_OPEN);
	if (ret)
		goto err3;

	return 0;

err3:
	free(msg);
err2:
	munmap(file_addr, bytes);
err1:
	close(fd);
	return ret;
}