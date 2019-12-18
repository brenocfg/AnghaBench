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
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_assertiontype_t ;

/* Variables and functions */
 int BACKTRACE_MAXFRAME ; 
 int /*<<< orphan*/  ISC_MSGSET_GENERAL ; 
 int /*<<< orphan*/  ISC_MSG_FAILED ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* isc_assertion_typetotext (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_backtrace_getsymbol (void*,char const**,unsigned long*) ; 
 scalar_t__ isc_backtrace_gettrace (void**,int,int*) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 char* isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
default_callback(const char *file, int line, isc_assertiontype_t type,
		 const char *cond)
{
	void *tracebuf[BACKTRACE_MAXFRAME];
	int i, nframes;
	const char *logsuffix = ".";
	const char *fname;
	isc_result_t result;

	result = isc_backtrace_gettrace(tracebuf, BACKTRACE_MAXFRAME, &nframes);
		if (result == ISC_R_SUCCESS && nframes > 0)
			logsuffix = ", back trace";

	fprintf(stderr, "%s:%d: %s(%s) %s%s\n",
		file, line, isc_assertion_typetotext(type), cond,
		isc_msgcat_get(isc_msgcat, ISC_MSGSET_GENERAL,
			       ISC_MSG_FAILED, "failed"), logsuffix);
	if (result == ISC_R_SUCCESS) {
		for (i = 0; i < nframes; i++) {
			unsigned long offset;

			fname = NULL;
			result = isc_backtrace_getsymbol(tracebuf[i], &fname,
							 &offset);
			if (result == ISC_R_SUCCESS) {
				fprintf(stderr, "#%d %p in %s()+0x%lx\n", i,
					tracebuf[i], fname, offset);
			} else {
				fprintf(stderr, "#%d %p in ??\n", i,
					tracebuf[i]);
			}
		}
	}
	fflush(stderr);
}