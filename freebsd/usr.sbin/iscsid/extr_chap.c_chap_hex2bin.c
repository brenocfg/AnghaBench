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
 int /*<<< orphan*/  assert (int) ; 
 char* calloc (size_t,int) ; 
 int chap_b642bin (char const*,void**,size_t*) ; 
 int chap_hex2int (char const) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,...) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static int
chap_hex2bin(const char *hex, void **binp, size_t *bin_lenp)
{
	int i, hex_len, nibble;
	bool lo = true; /* As opposed to 'hi'. */
	char *bin;
	size_t bin_off, bin_len;

	if (strncasecmp(hex, "0b", strlen("0b")) == 0)
		return (chap_b642bin(hex + 2, binp, bin_lenp));

	if (strncasecmp(hex, "0x", strlen("0x")) != 0) {
		log_warnx("malformed variable, should start with \"0x\""
		    " or \"0b\"");
		return (-1);
	}

	hex += strlen("0x");
	hex_len = strlen(hex);
	if (hex_len < 1) {
		log_warnx("malformed variable; doesn't contain anything "
		    "but \"0x\"");
		return (-1);
	}

	bin_len = hex_len / 2 + hex_len % 2;
	bin = calloc(bin_len, 1);
	if (bin == NULL)
		log_err(1, "calloc");

	bin_off = bin_len - 1;
	for (i = hex_len - 1; i >= 0; i--) {
		nibble = chap_hex2int(hex[i]);
		if (nibble < 0) {
			log_warnx("malformed variable, invalid char \"%c\"",
			    hex[i]);
			free(bin);
			return (-1);
		}

		assert(bin_off < bin_len);
		if (lo) {
			bin[bin_off] = nibble;
			lo = false;
		} else {
			bin[bin_off] |= nibble << 4;
			bin_off--;
			lo = true;
		}
	}

	*binp = bin;
	*bin_lenp = bin_len;
	return (0);
}