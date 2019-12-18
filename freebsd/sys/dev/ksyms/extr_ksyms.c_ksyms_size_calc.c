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
struct tsizes {scalar_t__ ts_strsz; scalar_t__ ts_symsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ksyms_size_permod ; 
 int /*<<< orphan*/  linker_file_foreach (int /*<<< orphan*/ ,struct tsizes*) ; 

__attribute__((used)) static void
ksyms_size_calc(struct tsizes *ts)
{

	ts->ts_symsz = 0;
	ts->ts_strsz = 0;

	(void)linker_file_foreach(ksyms_size_permod, ts);
}