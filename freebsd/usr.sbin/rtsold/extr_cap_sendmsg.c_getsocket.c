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
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  CAP_CONNECT ; 
 int /*<<< orphan*/  CAP_SEND ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
getsocket(int *sockp, int proto)
{
	cap_rights_t rights;
	int sock;

	if (*sockp >= 0)
		return (0);

	if ((sock = socket(AF_INET6, SOCK_RAW, proto)) < 0)
		return (-1);
	cap_rights_init(&rights, CAP_CONNECT, CAP_SEND);
	if (caph_rights_limit(sock, &rights) != 0)
		return (-1);
	*sockp = sock;

	return (0);
}