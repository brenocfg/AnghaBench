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
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 size_t strlen (char const*) ; 
 float strtof (char const*,char**) ; 
 scalar_t__ strtol (char const*,char**,int) ; 

__attribute__((used)) static int
strIKtoi(const char *str, char **endptrp, const char *fmt)
{
	int kelv;
	float temp;
	size_t len;
	const char *p;
	int prec, i;

	assert(errno == 0);

	len = strlen(str);
	/* caller already checked this */
	assert(len > 0);

	/*
	 * A format of "IK" is in deciKelvin. A format of "IK3" is in
	 * milliKelvin. The single digit following IK is log10 of the
	 * multiplying factor to convert Kelvin into the untis of this sysctl,
	 * or the dividing factor to convert the sysctl value to Kelvin. Numbers
	 * larger than 6 will run into precision issues with 32-bit integers.
	 * Characters that aren't ASCII digits after the 'K' are ignored. No
	 * localization is present because this is an interface from the kernel
	 * to this program (eg not an end-user interface), so isdigit() isn't
	 * used here.
	 */
	if (fmt[2] != '\0' && fmt[2] >= '0' && fmt[2] <= '9')
		prec = fmt[2] - '0';
	else
		prec = 1;
	p = &str[len - 1];
	if (*p == 'C' || *p == 'F' || *p == 'K') {
		temp = strtof(str, endptrp);
		if (*endptrp != str && *endptrp == p && errno == 0) {
			if (*p == 'F')
				temp = (temp - 32) * 5 / 9;
			*endptrp = NULL;
			if (*p != 'K')
				temp += 273.15;
			for (i = 0; i < prec; i++)
				temp *= 10.0;
			return ((int)(temp + 0.5));
		}
	} else {
		/* No unit specified -> treat it as a raw number */
		kelv = (int)strtol(str, endptrp, 10);
		if (*endptrp != str && *endptrp == p && errno == 0) {
			*endptrp = NULL;
			return (kelv);
		}
	}

	errno = ERANGE;
	return (0);
}