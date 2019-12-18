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
typedef  int /*<<< orphan*/  sun ;
struct sockaddr_un {int sun_len; scalar_t__* sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  FAIL (char*,...) ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print (char*,struct sockaddr_un*,int) ; 

__attribute__((used)) static int
acc(int s)
{
	char guard1;
	struct sockaddr_un sun;
	char guard2;
	socklen_t len;

	guard1 = guard2 = 's';

	memset(&sun, 0, sizeof(sun));
	len = sizeof(sun);
	if ((s = accept(s, (struct sockaddr *)&sun, &len)) == -1)
		FAIL("accept");
	if (guard1 != 's')
		FAIL("guard1 = '%c'", guard1);
	if (guard2 != 's')
		FAIL("guard2 = '%c'", guard2);
#ifdef DEBUG
	print("accept", &sun, len);
#endif
	if (len != 2)
		FAIL("len %d != 2", len);
	if (sun.sun_family != AF_UNIX)
		FAIL("sun->sun_family %d != AF_UNIX", sun.sun_family);
#ifdef BSD4_4
	if (sun.sun_len != 2)
		FAIL("sun->sun_len %d != 2", sun.sun_len);
#endif
	for (size_t i = 0; i < sizeof(sun.sun_path); i++)
		if (sun.sun_path[i])
			FAIL("sun.sun_path[%zu] %d != NULL", i,
			    sun.sun_path[i]);
	return s;
fail:
	if (s != -1)
		close(s);
	return -1;
}