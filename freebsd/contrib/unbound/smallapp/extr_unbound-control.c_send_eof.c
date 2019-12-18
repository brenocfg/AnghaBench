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
typedef  int /*<<< orphan*/  e ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  remote_write (int /*<<< orphan*/ *,int,char*,int) ; 

__attribute__((used)) static void
send_eof(SSL* ssl, int fd)
{
	char e[] = {0x04, 0x0a};
	remote_write(ssl, fd, e, sizeof(e));
}