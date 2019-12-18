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
struct passwd {char* pw_name; char* pw_gecos; } ;

/* Variables and functions */
 scalar_t__ errno ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 

__attribute__((used)) static struct passwd *xgetpwuid_self(int *is_bogus)
{
	struct passwd *pw;

	errno = 0;
	pw = getpwuid(getuid());
	if (!pw) {
		static struct passwd fallback;
		fallback.pw_name = "unknown";
#ifndef NO_GECOS_IN_PWENT
		fallback.pw_gecos = "Unknown";
#endif
		pw = &fallback;
		if (is_bogus)
			*is_bogus = 1;
	}
	return pw;
}