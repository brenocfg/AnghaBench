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
typedef  scalar_t__ u_int8_t ;
struct ata_security_password {int ctrl; int /*<<< orphan*/  password; } ;
struct ata_cmd {scalar_t__ command; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int ATA_SECURITY_LEVEL_MAXIMUM ; 
 int ATA_SECURITY_PASSWORD_MASTER ; 
 scalar_t__ ATA_SECURITY_SET_PASSWORD ; 
 char* ata_op_string (struct ata_cmd*) ; 
 int /*<<< orphan*/  bzero (struct ata_cmd*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
atasecurity_notify(u_int8_t command, struct ata_security_password *pwd)
{
	struct ata_cmd cmd;

	bzero(&cmd, sizeof(cmd));
	cmd.command = command;
	printf("Issuing %s", ata_op_string(&cmd));

	if (pwd != NULL) {
		char pass[sizeof(pwd->password)+1];

		/* pwd->password may not be null terminated */
		pass[sizeof(pwd->password)] = '\0';
		strncpy(pass, pwd->password, sizeof(pwd->password));
		printf(" password='%s', user='%s'",
			pass,
			(pwd->ctrl & ATA_SECURITY_PASSWORD_MASTER) ?
			"master" : "user");

		if (command == ATA_SECURITY_SET_PASSWORD) {
			printf(", mode='%s'",
			       (pwd->ctrl & ATA_SECURITY_LEVEL_MAXIMUM) ?
			       "maximum" : "high");
		}
	}

	printf("\n");
}