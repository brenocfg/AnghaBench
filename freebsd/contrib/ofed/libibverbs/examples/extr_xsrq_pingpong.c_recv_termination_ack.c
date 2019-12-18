#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* rem_dest; } ;
struct TYPE_3__ {int sockfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERMINATION_MSG ; 
 int TERMINATION_MSG_SIZE ; 
 TYPE_2__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recv_termination_ack(int index)
{
	char msg[TERMINATION_MSG_SIZE];
	int n = 0, r;
	int sockfd = ctx.rem_dest[index].sockfd;

	while (n < TERMINATION_MSG_SIZE) {
		r = read(sockfd, msg + n, TERMINATION_MSG_SIZE - n);
		if (r < 0) {
			perror("client read");
			fprintf(stderr,
				"%d/%d: Couldn't read remote termination ack\n",
				n, TERMINATION_MSG_SIZE);
			return 1;
		}
		n += r;
	}

	if (strcmp(msg, TERMINATION_MSG)) {
		fprintf(stderr, "Invalid termination ack was accepted\n");
		return 1;
	}

	return 0;
}