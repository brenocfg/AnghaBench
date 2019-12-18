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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test ; 

__attribute__((used)) static void
my_getsockname(int s, struct sockaddr *sa, socklen_t *salen)
{

	if (getsockname(s, sa, salen) < 0)
		err(-1, "%s: getsockname", test);
}