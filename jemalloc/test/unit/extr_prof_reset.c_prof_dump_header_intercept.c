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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  prof_cnt_t ;

/* Variables and functions */
 int /*<<< orphan*/  cnt_all_copy ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int prof_dump_header_intercepted ; 

__attribute__((used)) static bool
prof_dump_header_intercept(tsdn_t *tsdn, bool propagate_err,
    const prof_cnt_t *cnt_all) {
	prof_dump_header_intercepted = true;
	memcpy(&cnt_all_copy, cnt_all, sizeof(prof_cnt_t));

	return false;
}