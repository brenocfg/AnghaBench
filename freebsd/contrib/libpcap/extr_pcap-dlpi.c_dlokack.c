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

/* Variables and functions */
 int /*<<< orphan*/  DL_OK_ACK_SIZE ; 
 int recv_ack (int,int /*<<< orphan*/ ,char const*,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dlokack(int fd, const char *what, char *bufp, char *ebuf)
{

	return (recv_ack(fd, DL_OK_ACK_SIZE, what, bufp, ebuf, NULL));
}