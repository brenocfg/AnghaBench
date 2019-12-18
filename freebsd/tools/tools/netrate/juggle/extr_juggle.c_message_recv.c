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
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int MESSAGELEN ; 
 int /*<<< orphan*/  errno ; 
 int read (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
message_recv(int s)
{
	u_char buffer[MESSAGELEN];
	ssize_t len;

	len = read(s, buffer, sizeof(buffer));
	if (len == -1)
		return (-1);
	if (len != sizeof(buffer)) {
		errno = EMSGSIZE;
		return (-1);
	}
	return (0);
}