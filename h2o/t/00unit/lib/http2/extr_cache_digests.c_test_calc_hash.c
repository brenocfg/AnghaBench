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

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int calc_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_calc_hash(void)
{
    ok(calc_hash(H2O_STRLIT("https://example.com/style.css"), H2O_STRLIT("")) == 0xbaf9e86f03330860);
    ok(calc_hash(H2O_STRLIT("https://example.com/style.css"), H2O_STRLIT("\"deadbeef\"")) == 0xa53eb398509042d7);
}