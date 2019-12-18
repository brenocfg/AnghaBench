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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINTF (int,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int VE_MUST ; 
 int VE_WANT ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 unsigned char* read_fd (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  ve_self_tests () ; 
 size_t ve_trust_anchors_add_buf (unsigned char*,int /*<<< orphan*/ ) ; 
 size_t ve_trust_anchors_revoke (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verify_tweak(int fd, off_t off, struct stat *stp,
    char *tweak, int *accept_no_fp,
    int *verbose, int *verifying)
{
	if (strcmp(tweak, "off") == 0) {
		*verifying = 0;
	} else if (strcmp(tweak, "strict") == 0) {
		/* anything caller wants verified must be */
		*accept_no_fp = VE_WANT;
		*verbose = 1; /* warn of anything unverified */
		/* treat self test failure as fatal */
		if (!ve_self_tests()) {
			panic("verify self tests failed");
		}
	} else if (strcmp(tweak, "modules") == 0) {
		/* modules/kernel must be verified */
		*accept_no_fp = VE_MUST;
	} else if (strcmp(tweak, "try") == 0) {
		/* best effort: always accept no fp */
		*accept_no_fp = VE_MUST + 1;
	} else if (strcmp(tweak, "verbose") == 0) {
		*verbose = 1;
	} else if (strcmp(tweak, "quiet") == 0) {
		*verbose = 0;
	} else if (strncmp(tweak, "trust", 5) == 0) {
		/* content is trust anchor to add or revoke */
		unsigned char *ucp;
		size_t num;

		if (off > 0)
			lseek(fd, 0, SEEK_SET);
		ucp = read_fd(fd, stp->st_size);
		if (ucp == NULL)
			return;
		if (strstr(tweak, "revoke")) {
			num = ve_trust_anchors_revoke(ucp, stp->st_size);
			DEBUG_PRINTF(3, ("revoked %d trust anchors\n",
				(int) num));
		} else {
			num = ve_trust_anchors_add_buf(ucp, stp->st_size);
			DEBUG_PRINTF(3, ("added %d trust anchors\n",
				(int) num));
		}
	}
}