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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int getbits (char const*,int*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
getv4(const char *src, u_char *dst, int *bitsp) {
	static const char digits[] = "0123456789";
	u_char *odst = dst;
	int n;
	u_int val;
	char ch;

	val = 0;
	n = 0;
	while ((ch = *src++) != '\0') {
		const char *pch;

		pch = strchr(digits, ch);
		if (pch != NULL) {
			if (n++ != 0 && val == 0)	/*%< no leading zeros */
				return (0);
			val *= 10;
			val += (pch - digits);
			if (val > 255)			/*%< range */
				return (0);
			continue;
		}
		if (ch == '.' || ch == '/') {
			if (dst - odst > 3)		/*%< too many octets? */
				return (0);
			*dst++ = val;
			if (ch == '/')
				return (getbits(src, bitsp));
			val = 0;
			n = 0;
			continue;
		}
		return (0);
	}
	if (n == 0)
		return (0);
	if (dst - odst > 3)		/*%< too many octets? */
		return (0);
	*dst++ = val;
	return (1);
}