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
struct pf_altq {scalar_t__ qid; } ;
struct pfioc_altq {unsigned int nr; struct pf_altq altq; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  pfioc ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETALTQ ; 
 int /*<<< orphan*/  DIOCGETALTQS ; 
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PFIOC_ALTQ_VERSION ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pf_altq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  altq_entries ; 
 int /*<<< orphan*/  bzero (struct pfioc_altq*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  entries ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_altq*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 struct pf_altq* safe_calloc (int,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
altq_fetch(void)
{
	struct pfioc_altq pfioc;
	struct pf_altq *altq;
	int pffd;
	unsigned int mnr;
	static int altq_fetched = 0;

	if (altq_fetched)
		return;
	altq_fetched = 1;
	pffd = open("/dev/pf", O_RDONLY);
	if (pffd == -1) {
		warn("altq support opening pf(4) control device");
		return;
	}
	bzero(&pfioc, sizeof(pfioc));
	pfioc.version = PFIOC_ALTQ_VERSION;
	if (ioctl(pffd, DIOCGETALTQS, &pfioc) != 0) {
		warn("altq support getting queue list");
		close(pffd);
		return;
	}
	mnr = pfioc.nr;
	for (pfioc.nr = 0; pfioc.nr < mnr; pfioc.nr++) {
		if (ioctl(pffd, DIOCGETALTQ, &pfioc) != 0) {
			if (errno == EBUSY)
				break;
			warn("altq support getting queue list");
			close(pffd);
			return;
		}
		if (pfioc.altq.qid == 0)
			continue;
		altq = safe_calloc(1, sizeof(*altq));
		*altq = pfioc.altq;
		TAILQ_INSERT_TAIL(&altq_entries, altq, entries);
	}
	close(pffd);
}