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
struct msg_hdr {int len; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLOSE ; 
 int /*<<< orphan*/  bytes ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_addr ; 
 int /*<<< orphan*/  memset (struct msg_hdr*,int /*<<< orphan*/ ,int) ; 
 int msg_get_resp (int,struct msg_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rsend (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_close(int rs)
{
	struct msg_hdr msg;
	int ret;

	printf("closing...");
	fflush(NULL);
	memset(&msg, 0, sizeof msg);
	msg.command = CMD_CLOSE;
	msg.len = sizeof msg;
	ret = rsend(rs, (char *) &msg, msg.len, 0);
	if (ret != msg.len)
		goto out;

	ret = msg_get_resp(rs, &msg, CMD_CLOSE);
	if (ret)
		goto out;

	printf("done\n");
out:
	munmap(file_addr, bytes);
	close(fd);
	return ret;
}