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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* parseint (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static char *parse256(char *arg, uint8_t *buf)
{
	int numdigits = 0;
	int startindex;
	char *ptr;
	int i;

	if (!strncmp(arg, "0x", 2) || !strncmp(arg, "0X", 2))
		arg += 2;

	for (ptr = arg; *ptr; ptr++) {
		if (!isxdigit(*ptr))
			return "invalid hex digit read";
		numdigits++;
	}

	if (numdigits > 64)
		return "hex code too long";

	/* we need to imagine that this is like a 256-bit int stored
	 * in big endian.  So we need to find the first index
	 * point where the user's input would start in our array.
	 */
	startindex = 32 - ((numdigits - 1) / 2) - 1;

	for (i = startindex; i <= 31; i++) {
		char tmp[3] = { 0 };
		uint32_t tmpint;
		char *errstr;

		/* I can't help but think there is a strtoX that
		 * will do this for me, but I can't find it.
		 */
		if (i == startindex && numdigits % 2) {
			memcpy(tmp, arg, 1);
			arg++;
		}
		else {
			memcpy(tmp, arg, 2);
			arg += 2;
		}

		if ((errstr = parseint(tmp, &tmpint, 1)))
			return errstr;
		buf[i] = tmpint;
	}

	return NULL;
}