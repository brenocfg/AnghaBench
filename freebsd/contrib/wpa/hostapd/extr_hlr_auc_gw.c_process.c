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
struct sockaddr_un {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  os_strlen (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ process_cmd (char*,char*,int) ; 
 size_t recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ sendto (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

__attribute__((used)) static int process(int s)
{
	char buf[1000], resp[1000];
	struct sockaddr_un from;
	socklen_t fromlen;
	ssize_t res;

	fromlen = sizeof(from);
	res = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &from,
		       &fromlen);
	if (res < 0) {
		perror("recvfrom");
		return -1;
	}

	if (res == 0)
		return 0;

	if ((size_t) res >= sizeof(buf))
		res = sizeof(buf) - 1;
	buf[res] = '\0';

	printf("Received: %s\n", buf);

	if (process_cmd(buf, resp, sizeof(resp)) < 0) {
		printf("Failed to process request\n");
		return -1;
	}

	if (resp[0] == '\0') {
		printf("No response\n");
		return 0;
	}

	printf("Send: %s\n", resp);

	if (sendto(s, resp, os_strlen(resp), 0, (struct sockaddr *) &from,
		   fromlen) < 0)
		perror("send");

	return 0;
}