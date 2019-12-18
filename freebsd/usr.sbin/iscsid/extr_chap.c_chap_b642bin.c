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
 int b64_pton (char const*,char*,int) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
chap_b642bin(const char *b64, void **binp, size_t *bin_lenp)
{
	char *bin;
	int b64_len, bin_len;

	b64_len = strlen(b64);
	bin_len = (b64_len + 3) / 4 * 3;
	bin = calloc(bin_len, 1);
	if (bin == NULL)
		log_err(1, "calloc");

	bin_len = b64_pton(b64, bin, bin_len);
	if (bin_len < 0) {
		log_warnx("malformed base64 variable");
		free(bin);
		return (-1);
	}
	*binp = bin;
	*bin_lenp = bin_len;
	return (0);
}