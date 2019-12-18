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
typedef  int /*<<< orphan*/  uintmax_t ;
struct memory_type_list {int dummy; } ;
struct memory_type {int dummy; } ;

/* Variables and functions */
 int MEMSTAT_ERROR_KVM ; 
 int /*<<< orphan*/  MEMTYPE_MAXNAME ; 
 int /*<<< orphan*/ * kd ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 scalar_t__ memstat_get_count (struct memory_type*) ; 
 scalar_t__ memstat_get_countlimit (struct memory_type*) ; 
 scalar_t__ memstat_get_failures (struct memory_type*) ; 
 scalar_t__ memstat_get_free (struct memory_type*) ; 
 int /*<<< orphan*/  memstat_get_name (struct memory_type*) ; 
 scalar_t__ memstat_get_numallocs (struct memory_type*) ; 
 scalar_t__ memstat_get_size (struct memory_type*) ; 
 scalar_t__ memstat_get_sleeps (struct memory_type*) ; 
 scalar_t__ memstat_get_xdomain (struct memory_type*) ; 
 scalar_t__ memstat_kvm_uma (struct memory_type_list*,int /*<<< orphan*/ *) ; 
 struct memory_type_list* memstat_mtl_alloc () ; 
 struct memory_type* memstat_mtl_first (struct memory_type_list*) ; 
 int /*<<< orphan*/  memstat_mtl_free (struct memory_type_list*) ; 
 int memstat_mtl_geterror (struct memory_type_list*) ; 
 struct memory_type* memstat_mtl_next (struct memory_type*) ; 
 int /*<<< orphan*/  memstat_strerror (int) ; 
 scalar_t__ memstat_sysctl_uma (struct memory_type_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int /*<<< orphan*/  xo_warn (char*) ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
domemstat_zone(void)
{
	struct memory_type_list *mtlp;
	struct memory_type *mtp;
	int error;
	char name[MEMTYPE_MAXNAME + 1];

	mtlp = memstat_mtl_alloc();
	if (mtlp == NULL) {
		xo_warn("memstat_mtl_alloc");
		return;
	}
	if (kd == NULL) {
		if (memstat_sysctl_uma(mtlp, 0) < 0) {
			xo_warnx("memstat_sysctl_uma: %s",
			    memstat_strerror(memstat_mtl_geterror(mtlp)));
			return;
		}
	} else {
		if (memstat_kvm_uma(mtlp, kd) < 0) {
			error = memstat_mtl_geterror(mtlp);
			if (error == MEMSTAT_ERROR_KVM)
				xo_warnx("memstat_kvm_uma: %s",
				    kvm_geterr(kd));
			else
				xo_warnx("memstat_kvm_uma: %s",
				    memstat_strerror(error));
		}
	}
	xo_open_container("memory-zone-statistics");
	xo_emit("{T:/%-20s} {T:/%6s} {T:/%6s} {T:/%8s} {T:/%8s} {T:/%8s} {T:/%8s}"
	    "{T:/%4s} {T:/%4s}\n\n", "ITEM", "SIZE",
	    "LIMIT", "USED", "FREE", "REQ", "FAIL", "SLEEP", "XDOMAIN");
	xo_open_list("zone");
	for (mtp = memstat_mtl_first(mtlp); mtp != NULL;
	    mtp = memstat_mtl_next(mtp)) {
		strlcpy(name, memstat_get_name(mtp), MEMTYPE_MAXNAME);
		strcat(name, ":");
		xo_open_instance("zone");
		xo_emit("{d:name/%-20s}{ke:name/%s} {:size/%6ju}, "
		    "{:limit/%6ju},{:used/%8ju},"
		    "{:free/%8ju},{:requests/%8ju},"
		    "{:fail/%4ju},{:sleep/%4ju},{:xdomain/%4ju}\n", name,
		    memstat_get_name(mtp),
		    (uintmax_t)memstat_get_size(mtp),
		    (uintmax_t)memstat_get_countlimit(mtp),
		    (uintmax_t)memstat_get_count(mtp),
		    (uintmax_t)memstat_get_free(mtp),
		    (uintmax_t)memstat_get_numallocs(mtp),
		    (uintmax_t)memstat_get_failures(mtp),
		    (uintmax_t)memstat_get_sleeps(mtp),
		    (uintmax_t)memstat_get_xdomain(mtp));
		xo_close_instance("zone");
	}
	memstat_mtl_free(mtlp);
	xo_close_list("zone");
	xo_close_container("memory-zone-statistics");
	xo_emit("\n");
}