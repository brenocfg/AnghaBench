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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  basic_test (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  open_file_ro_unlink ; 

__attribute__((used)) static void
read_unlinked(const atf_tc_t *tc, const char *mp)
{

	basic_test(tc, mp, EBUSY, false, open_file_ro_unlink, close_file);
}