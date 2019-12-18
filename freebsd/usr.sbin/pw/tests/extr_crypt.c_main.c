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

/* Variables and functions */
 char* crypt (char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int main(int argc, char** argv)
{
	char *salt, *pass, *hash;

	if (argc < 3)
		errx(1, "Usage: crypt <salt> <password>");
	salt = argv[1];
	pass = argv[2];

	hash = crypt(pass, salt);
	printf("%s", hash);
	return (hash == NULL ? 1 : 0);
}