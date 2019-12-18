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
 scalar_t__ EINPROGRESS ; 
 scalar_t__ connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  test ; 

__attribute__((used)) static void
my_connect(int sock, struct sockaddr *sa, socklen_t len)
{

	if (connect(sock, sa, len) < 0 && errno != EINPROGRESS)
		err(-1, "%s: connect", test);
}