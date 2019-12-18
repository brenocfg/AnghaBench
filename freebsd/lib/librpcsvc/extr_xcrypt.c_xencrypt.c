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
 int DES_ENCRYPT ; 
 scalar_t__ DES_FAILED (int) ; 
 int DES_HW ; 
 int /*<<< orphan*/  bin2hex (int,unsigned char*,char*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int cbc_crypt (char*,char*,int,int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hex2bin (int,char*,char*) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  passwd2des (char*,char*) ; 
 int strlen (char*) ; 

int
xencrypt(char *secret, char *passwd)
{
	char key[8];
	char ivec[8];
	char *buf;
	int err;
	int len;

	len = strlen(secret) / 2;
	if ((buf = malloc((unsigned)len)) == NULL) {
		return(0);
	}

	hex2bin(len, secret, buf);
	passwd2des(passwd, key);
	bzero(ivec, 8);

	err = cbc_crypt(key, buf, len, DES_ENCRYPT | DES_HW, ivec);
	if (DES_FAILED(err)) {	
		free(buf);
		return (0);
	}
	bin2hex(len, (unsigned char *) buf, secret);
	free(buf);
	return (1);
}