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
struct knote {int /*<<< orphan*/  kn_fp; } ;

/* Variables and functions */
 int fo_kqfilter (int /*<<< orphan*/ ,struct knote*) ; 

__attribute__((used)) static int
filt_fileattach(struct knote *kn)
{

	return (fo_kqfilter(kn->kn_fp, kn));
}