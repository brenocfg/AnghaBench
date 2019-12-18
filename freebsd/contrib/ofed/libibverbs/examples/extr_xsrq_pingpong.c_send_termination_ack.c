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
 char* TERMINATION_FORMAT ; 
 int /*<<< orphan*/  TERMINATION_MSG ; 
 int TERMINATION_MSG_SIZE ; 
 TYPE_2__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int send_termination_ack(int index)
{
	char msg[TERMINATION_MSG_SIZE];
	int sockfd = ctx.rem_dest[index].sockfd;

	sprintf(msg, TERMINATION_FORMAT, TERMINATION_MSG);

	if (write(sockfd, msg, TERMINATION_MSG_SIZE) != TERMINATION_MSG_SIZE) {
		fprintf(stderr, "Couldn't send termination ack\n");
		return 1;
	}

	return 0;
}