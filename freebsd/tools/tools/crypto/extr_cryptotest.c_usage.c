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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
usage(const char* cmd)
{
	printf("usage: %s [-czsbv] [-d dev] [-a algorithm] [count] [size ...]\n",
		cmd);
	printf("where algorithm is one of:\n");
	printf("    null des 3des (default) blowfish cast skipjack rij\n");
	printf("    aes aes192 aes256 chacha20 md5 sha1 sha256 sha384 sha512\n");
	printf("    blake2b blake2s\n");
	printf(" or an encryption algorithm concatented with authentication\n");
	printf(" algorithm with '+' in the middle, e.g., aes+sha1.\n");
	printf("count is the number of encrypt/decrypt ops to do\n");
	printf("size is the number of bytes of text to encrypt+decrypt\n");
	printf("\n");
	printf("-c check the results (slows timing)\n");
	printf("-d use specific device, specify 'soft' for testing software implementations\n");
	printf("\tNOTE: to use software you must set:\n\t sysctl kern.cryptodevallowsoft=1\n");
	printf("-z run all available algorithms on a variety of sizes\n");
	printf("-v be verbose\n");
	printf("-b mark operations for batching\n");
	printf("-p profile kernel crypto operation (must be root)\n");
	printf("-t n for n threads and run tests concurrently\n");
	exit(-1);
}