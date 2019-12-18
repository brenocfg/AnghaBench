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
struct in_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,struct in_addr*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

char *
inet_ntoa(struct in_addr in) {
	static char ret[18];

	strcpy(ret, "[inet_ntoa error]");
	(void) inet_ntop(AF_INET, &in, ret, sizeof ret);
	return (ret);
}