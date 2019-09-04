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
typedef  int /*<<< orphan*/  h2o_http2_casper_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 unsigned int calc_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_http2_casper_create (int,int) ; 
 int /*<<< orphan*/  h2o_http2_casper_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,char*,int) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_calc_key(void)
{
    h2o_http2_casper_t *casper = h2o_http2_casper_create(13, 6);

    unsigned key = calc_key(casper, H2O_STRLIT("/index.html")), expected;
    memcpy(&expected, "\x14\xfe\x45\x59", 4);
    expected &= (1 << 13) - 1;
    ok(key == expected);

    h2o_http2_casper_destroy(casper);
}