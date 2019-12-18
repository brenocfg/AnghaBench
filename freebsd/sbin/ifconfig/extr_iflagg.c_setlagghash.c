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
struct lagg_reqflags {int /*<<< orphan*/  rf_ifname; int /*<<< orphan*/  rf_flags; } ;
struct afswtch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAGG_F_HASHL2 ; 
 int /*<<< orphan*/  LAGG_F_HASHL3 ; 
 int /*<<< orphan*/  LAGG_F_HASHL4 ; 
 int /*<<< orphan*/  SIOCSLAGGHASH ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct lagg_reqflags*) ; 
 int /*<<< orphan*/  name ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
setlagghash(const char *val, int d, int s, const struct afswtch *afp)
{
	struct lagg_reqflags rf;
	char *str, *tmp, *tok;


	rf.rf_flags = 0;
	str = tmp = strdup(val);
	while ((tok = strsep(&tmp, ",")) != NULL) {
		if (strcmp(tok, "l2") == 0)
			rf.rf_flags |= LAGG_F_HASHL2;
		else if (strcmp(tok, "l3") == 0)
			rf.rf_flags |= LAGG_F_HASHL3;
		else if (strcmp(tok, "l4") == 0)
			rf.rf_flags |= LAGG_F_HASHL4;
		else
			errx(1, "Invalid lagghash option: %s", tok);
	}
	free(str);
	if (rf.rf_flags == 0)
		errx(1, "No lagghash options supplied");

	strlcpy(rf.rf_ifname, name, sizeof(rf.rf_ifname));
	if (ioctl(s, SIOCSLAGGHASH, &rf))
		err(1, "SIOCSLAGGHASH");
}