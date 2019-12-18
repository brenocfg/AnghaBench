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
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_NOSUB ; 
 int S_NSYMTYPES ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * sym_regex ; 
 int /*<<< orphan*/ * sym_regex_c ; 
 int /*<<< orphan*/ * sym_regex_kernel ; 
 int /*<<< orphan*/ * sym_regex_realmode ; 

__attribute__((used)) static void regex_init(int use_real_mode)
{
        char errbuf[128];
        int err;
	int i;

	if (use_real_mode)
		sym_regex = sym_regex_realmode;
	else
		sym_regex = sym_regex_kernel;

	for (i = 0; i < S_NSYMTYPES; i++) {
		if (!sym_regex[i])
			continue;

		err = regcomp(&sym_regex_c[i], sym_regex[i],
			      REG_EXTENDED|REG_NOSUB);

		if (err) {
			regerror(err, &sym_regex_c[i], errbuf, sizeof(errbuf));
			die("%s", errbuf);
		}
        }
}