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
struct linger {int l_onoff; scalar_t__ l_linger; } ;
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  l ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void
frob_socket(evutil_socket_t sock)
{
#ifdef EVENT__HAVE_STRUCT_LINGER
	struct linger l;
#endif
	int one = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&one, sizeof(one))<0)
		perror("setsockopt(SO_REUSEADDR)");
#ifdef EVENT__HAVE_STRUCT_LINGER
	l.l_onoff = 1;
	l.l_linger = 0;
	if (setsockopt(sock, SOL_SOCKET, SO_LINGER, (void*)&l, sizeof(l))<0)
		perror("setsockopt(SO_LINGER)");
#endif
}