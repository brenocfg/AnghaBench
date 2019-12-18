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
 int h2o_filecache_compare_etag_strong (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_strong_etag_cmp()
{
    /* example from RFC 7232 */
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("W/\"1\""), H2O_STRLIT("W/\"1\"")));
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("W/\"1\""), H2O_STRLIT("W/\"2\"")));
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("W/\"1\""), H2O_STRLIT("\"1\"")));
    ok(h2o_filecache_compare_etag_strong(H2O_STRLIT("\"1\""), H2O_STRLIT("\"1\"")));
    /* illegal etags */
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("\"1"), H2O_STRLIT("\"1\"")));
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("\"1\""), H2O_STRLIT("\"1")));
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("\"1"), H2O_STRLIT("\"1")));
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("1\""), H2O_STRLIT("\"1\"")));
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("\"1\""), H2O_STRLIT("1\"")));
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT("1\""), H2O_STRLIT("1\"")));
    ok(!h2o_filecache_compare_etag_strong(H2O_STRLIT(""), H2O_STRLIT("")));
}