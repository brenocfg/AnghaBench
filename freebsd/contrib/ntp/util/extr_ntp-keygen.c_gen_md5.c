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
typedef  char u_char ;
typedef  int /*<<< orphan*/  temp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MD5KEYS ; 
 int MD5SIZE ; 
 int /*<<< orphan*/  RAND_bytes (char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fheader (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  groupname ; 
 int ntp_crypto_random_buf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int
gen_md5(
	const char *id		/* file name id */
	)
{
	u_char	md5key[MD5SIZE + 1];	/* MD5 key */
	FILE	*str;
	int	i, j;
#ifdef OPENSSL
	u_char	keystr[MD5SIZE];
	u_char	hexstr[2 * MD5SIZE + 1];
	u_char	hex[] = "0123456789abcdef";
#endif	/* OPENSSL */

	str = fheader("MD5key", id, groupname);
	for (i = 1; i <= MD5KEYS; i++) {
		for (j = 0; j < MD5SIZE; j++) {
			u_char temp;

			while (1) {
				int rc;

				rc = ntp_crypto_random_buf(
				    &temp, sizeof(temp));
				if (-1 == rc) {
					fprintf(stderr, "ntp_crypto_random_buf() failed.\n");
					exit (-1);
				}
				if (temp == '#')
					continue;

				if (temp > 0x20 && temp < 0x7f)
					break;
			}
			md5key[j] = temp;
		}
		md5key[j] = '\0';
		fprintf(str, "%2d MD5 %s  # MD5 key\n", i,
		    md5key);
	}
#ifdef OPENSSL
	for (i = 1; i <= MD5KEYS; i++) {
		RAND_bytes(keystr, 20);
		for (j = 0; j < MD5SIZE; j++) {
			hexstr[2 * j] = hex[keystr[j] >> 4];
			hexstr[2 * j + 1] = hex[keystr[j] & 0xf];
		}
		hexstr[2 * MD5SIZE] = '\0';
		fprintf(str, "%2d SHA1 %s  # SHA1 key\n", i + MD5KEYS,
		    hexstr);
	}
#endif	/* OPENSSL */
	fclose(str);
	return (1);
}