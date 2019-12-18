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
typedef  int uid_t ;
typedef  int gid_t ;

/* Variables and functions */
 int getresgid (int*,int*,int*) ; 
 int getresuid (int*,int*,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
reportprivilege(char *message)
{
	uid_t euid, ruid, suid;
	gid_t egid, rgid, sgid;
	int error;

	error = getresuid(&ruid, &euid, &suid);
	if (error) {
		perror("getresuid");
		return (error);
	}

	error = getresgid(&rgid, &egid, &sgid);
	if (error) {
		perror("getresgid");
		return (error);
	}

	if (message)
		printf("%s: ", message);
	printf("ruid: %d, euid: %d, suid: %d,     ", ruid, euid, suid);
	printf("rgid: %d, egid: %d, sgid: %d\n", rgid, egid, sgid);

	return (0);
}