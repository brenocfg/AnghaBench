#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  l_siginfo_t ;
typedef  int /*<<< orphan*/  l_int ;
struct TYPE_3__ {int /*<<< orphan*/  ksi_info; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  siginfo_to_lsiginfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ksiginfo_to_lsiginfo(const ksiginfo_t *ksi, l_siginfo_t *lsi, l_int sig)
{

	siginfo_to_lsiginfo(&ksi->ksi_info, lsi, sig);
}