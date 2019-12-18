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
 int /*<<< orphan*/  CMD_WRITE ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 size_t bytes ; 
 int /*<<< orphan*/  client_close (int) ; 
 int client_connect () ; 
 int client_open (int) ; 
 int client_start_write (int) ; 
 int /*<<< orphan*/  end ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_addr ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int msg_get_resp (int,struct msg_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rclose (int) ; 
 size_t rsend (int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rshutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_perf () ; 
 int /*<<< orphan*/  start ; 

__attribute__((used)) static int client_run(void)
{
	struct msg_hdr ack;
	int ret, rs;
	size_t len;

	rs = client_connect();
	if (rs < 0)
		return rs;

	ret = client_open(rs);
	if (ret)
		goto shutdown;

	ret = client_start_write(rs);
	if (ret)
		goto close;

	printf("...");
	fflush(NULL);
	gettimeofday(&start, NULL);
	len = rsend(rs, file_addr, bytes, 0);
	if (len == bytes)
		ret = msg_get_resp(rs, &ack, CMD_WRITE);
	else
		ret = (int) len;

	gettimeofday(&end, NULL);

close:
	client_close(rs);
shutdown:
	rshutdown(rs, SHUT_RDWR);
	rclose(rs);
	if (!ret)
		show_perf();
	return ret;
}