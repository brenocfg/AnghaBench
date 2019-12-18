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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  password_hash ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nt_password_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strlen (char*) ; 

int main(int argc, char *argv[])
{
	unsigned char password_hash[16];
	size_t i;
	char *password, buf[64], *pos;

	if (argc > 1)
		password = argv[1];
	else {
		if (fgets(buf, sizeof(buf), stdin) == NULL) {
			printf("Failed to read password\n");
			return 1;
		}
		buf[sizeof(buf) - 1] = '\0';
		pos = buf;
		while (*pos != '\0') {
			if (*pos == '\r' || *pos == '\n') {
				*pos = '\0';
				break;
			}
			pos++;
		}
		password = buf;
	}

	if (nt_password_hash((u8 *) password, strlen(password), password_hash))
		return -1;
	for (i = 0; i < sizeof(password_hash); i++)
		printf("%02x", password_hash[i]);
	printf("\n");

	return 0;
}