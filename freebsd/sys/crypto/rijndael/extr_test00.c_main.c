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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  keyInstance ;
typedef  int /*<<< orphan*/  cipherInstance ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_DECRYPT ; 
 int LL ; 
 int /*<<< orphan*/  MODE_CBC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  rijndael_blockDecrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int*) ; 
 int /*<<< orphan*/  rijndael_cipherInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rijndael_makeKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
	keyInstance ki;
	cipherInstance ci;
	uint8_t key[16];
	uint8_t in[LL];
	uint8_t out[LL];
	int i, j;

	rijndael_cipherInit(&ci, MODE_CBC, NULL);
	for (i = 0; i < 16; i++)
		key[i] = i;
	rijndael_makeKey(&ki, DIR_DECRYPT, 128, key);
	for (i = 0; i < LL; i++)
		in[i] = i;
	rijndael_blockDecrypt(&ci, &ki, in, LL * 8, out);
	for (i = 0; i < LL; i++)
		printf("%02x", out[i]);
	putchar('\n');
	rijndael_blockDecrypt(&ci, &ki, in, LL * 8, in);
	j = 0;
	for (i = 0; i < LL; i++) {
		printf("%02x", in[i]);
		if (in[i] != out[i])
			j++;
	}
	putchar('\n');
	if (j != 0) {
		fprintf(stderr,
		    "Error: inplace decryption fails in %d places\n", j);
		return (1);
	} else {
		return (0);
	}
}