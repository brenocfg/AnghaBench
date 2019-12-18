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
struct eui64 {int dummy; } ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,...) ; 
 int EUI64_SIZ ; 
 scalar_t__ eui64_ntoa (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_eui64_id ; 
 int /*<<< orphan*/  test_eui64_id_ascii ; 

__attribute__((used)) static void
test_str(const char *str, const struct eui64 *eui)
{
	char a[EUI64_SIZ];

	ATF_REQUIRE_MSG(eui64_ntoa(&test_eui64_id, a, sizeof(a)) == 0,
	    "eui64_ntoa failed");
	ATF_REQUIRE_MSG(strcmp(a, test_eui64_id_ascii) == 0,
	    "the strings mismatched: `%s` != `%s`", a, test_eui64_id_ascii);
}