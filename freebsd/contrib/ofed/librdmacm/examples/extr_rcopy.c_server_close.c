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
struct msg_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bytes ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ fd ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file_addr ; 
 int /*<<< orphan*/  msg_send_resp (int,struct msg_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void server_close(int rs, struct msg_hdr *msg)
{
	printf("closing...");
	fflush(NULL);
	msg_send_resp(rs, msg, 0);

	if (file_addr) {
		munmap(file_addr, bytes);
		file_addr = NULL;
	}

	if (fd > 0) {
		close(fd);
		fd = 0;
	}
	printf("done\n");
}