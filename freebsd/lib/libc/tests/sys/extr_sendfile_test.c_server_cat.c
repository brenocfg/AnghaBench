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
typedef  size_t ssize_t ;

/* Variables and functions */
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_utils_create_file (char const*,char*,char*) ; 
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t recv (int,char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
server_cat(const char *dest_filename, int server_sock, size_t len)
{
	char *buffer, *buf_window_ptr;
	int recv_sock;
	size_t buffer_size;
	ssize_t received_bytes, recv_ret;

	/*
	 * Ensure that there isn't excess data sent across the wire by
	 * capturing 10 extra bytes (plus 1 for nul).
	 */
	buffer_size = len + 10 + 1;
	buffer = calloc(buffer_size, sizeof(char));
	if (buffer == NULL)
		err(1, "malloc failed");

	recv_sock = accept(server_sock, NULL, 0);
	if (recv_sock == -1)
		err(1, "accept failed");

	buf_window_ptr = buffer;
	received_bytes = 0;
	do {
		recv_ret = recv(recv_sock, buf_window_ptr,
		    buffer_size - received_bytes, 0);
		if (recv_ret <= 0)
			break;
		buf_window_ptr += recv_ret;
		received_bytes += recv_ret;
	} while (received_bytes < buffer_size);

	atf_utils_create_file(dest_filename, "%s", buffer);

	(void)close(recv_sock);
	(void)close(server_sock);
	free(buffer);

	if (received_bytes != len)
		errx(1, "received unexpected data: %zd != %zd", received_bytes,
		    len);
}