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
 scalar_t__ bslashchar (int) ; 
 int /*<<< orphan*/  domainchar (int) ; 
 scalar_t__ periodchar (int) ; 
 int res_hnok (char const*) ; 

int
res_mailok(const char *dn) {
	int ch, escaped = 0;

	/* "." is a valid missing representation */
	if (*dn == '\0')
		return (1);

	/* otherwise <label>.<hostname> */
	while ((ch = *dn++) != '\0') {
		if (!domainchar(ch))
			return (0);
		if (!escaped && periodchar(ch))
			break;
		if (escaped)
			escaped = 0;
		else if (bslashchar(ch))
			escaped = 1;
	}
	if (periodchar(ch))
		return (res_hnok(dn));
	return (0);
}