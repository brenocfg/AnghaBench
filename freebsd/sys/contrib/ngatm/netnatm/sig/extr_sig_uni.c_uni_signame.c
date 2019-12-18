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
typedef  enum uni_sig { ____Placeholder_uni_sig } uni_sig ;

/* Variables and functions */
 int UNIAPI_MAXSIG ; 
 char const** sig_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
uni_signame(enum uni_sig sig)
{
	static char buf[40];

	if (sig >= UNIAPI_MAXSIG) {
		sprintf(buf, "UNIAPI_SIG%u", sig);
		return (buf);
	}
	return (sig_names[sig]);
}