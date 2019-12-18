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
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alt_break_state ; 
 scalar_t__ bvm_rcons (unsigned char*) ; 
 int /*<<< orphan*/  kdb_alt_break (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bvm_cngetc(struct consdev *cp)
{
	unsigned char ch;

	if (bvm_rcons(&ch) == 0) {
#if defined(KDB)
		kdb_alt_break(ch, &alt_break_state);
#endif
		return (ch);
	}

	return (-1);
}