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
struct iconv_cspair {struct iconv_cspair* cp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ICONV ; 
 int /*<<< orphan*/  M_ICONVDATA ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct iconv_cspair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_link ; 
 int /*<<< orphan*/  free (struct iconv_cspair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iconv_cslist ; 

__attribute__((used)) static void
iconv_unregister_cspair(struct iconv_cspair *csp)
{
	TAILQ_REMOVE(&iconv_cslist, csp, cp_link);
	if (csp->cp_data)
		free(csp->cp_data, M_ICONVDATA);
	free(csp, M_ICONV);
}