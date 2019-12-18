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
typedef  int /*<<< orphan*/  const nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int INT64_MAX ; 
 int INT64_MIN ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int UINT64_MAX ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/  const*,char*,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_bool (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_descriptor (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_null (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/  const*,char*,char*) ; 
 int /*<<< orphan*/  nvlist_add_stringf (int /*<<< orphan*/  const*,char*,char*,...) ; 
 int /*<<< orphan*/  const* nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/  const*) ; 
 scalar_t__ nvlist_error (int /*<<< orphan*/  const*) ; 
 int nvlist_exists_binary (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_bool (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_descriptor (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_null (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_number (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* nvlist_get_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
main(void)
{
	const nvlist_t *cnvl;
	nvlist_t *nvl;

	printf("1..94\n");

	nvl = nvlist_create(0);

	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	nvlist_add_null(nvl, "nvlist/null");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_null(nvl, "nvlist/null"));

	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool/true"));
	nvlist_add_bool(nvl, "nvlist/bool/true", true);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_bool(nvl, "nvlist/bool/true"));

	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool/false"));
	nvlist_add_bool(nvl, "nvlist/bool/false", false);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_bool(nvl, "nvlist/bool/false"));

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/0"));
	nvlist_add_number(nvl, "nvlist/number/0", 0);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_number(nvl, "nvlist/number/0"));

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/1"));
	nvlist_add_number(nvl, "nvlist/number/1", 1);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_number(nvl, "nvlist/number/1"));

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/-1"));
	nvlist_add_number(nvl, "nvlist/number/-1", -1);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_number(nvl, "nvlist/number/-1"));

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/UINT64_MAX"));
	nvlist_add_number(nvl, "nvlist/number/UINT64_MAX", UINT64_MAX);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_number(nvl, "nvlist/number/UINT64_MAX"));

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/INT64_MIN"));
	nvlist_add_number(nvl, "nvlist/number/INT64_MIN", INT64_MIN);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_number(nvl, "nvlist/number/INT64_MIN"));

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/INT64_MAX"));
	nvlist_add_number(nvl, "nvlist/number/INT64_MAX", INT64_MAX);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_number(nvl, "nvlist/number/INT64_MAX"));

	CHECK(!nvlist_exists_string(nvl, "nvlist/string/"));
	nvlist_add_string(nvl, "nvlist/string/", "");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl, "nvlist/string/"));

	CHECK(!nvlist_exists_string(nvl, "nvlist/string/x"));
	nvlist_add_string(nvl, "nvlist/string/x", "x");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl, "nvlist/string/x"));

	CHECK(!nvlist_exists_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"));
	nvlist_add_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"));

	CHECK(!nvlist_exists_string(nvl, "nvlist/stringf/"));
	nvlist_add_stringf(nvl, "nvlist/stringf/", "%s", "");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl, "nvlist/stringf/"));

	CHECK(!nvlist_exists_string(nvl, "nvlist/stringf/x"));
	nvlist_add_stringf(nvl, "nvlist/stringf/x", "%s", "x");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl, "nvlist/stringf/x"));

	CHECK(!nvlist_exists_string(nvl, "nvlist/stringf/666Xabc"));
	nvlist_add_stringf(nvl, "nvlist/stringf/666Xabc", "%d%c%s", 666, 'X', "abc");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl, "nvlist/stringf/666Xabc"));

	CHECK(!nvlist_exists_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO"));
	nvlist_add_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO", STDERR_FILENO);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO"));

	CHECK(!nvlist_exists_binary(nvl, "nvlist/binary/x"));
	nvlist_add_binary(nvl, "nvlist/binary/x", "x", 1);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary/x"));

	CHECK(!nvlist_exists_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));
	nvlist_add_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", sizeof("abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));

	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	nvlist_add_nvlist(nvl, "nvlist/nvlist", nvl);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));

	CHECK(nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(nvlist_exists_bool(nvl, "nvlist/bool/true"));
	CHECK(nvlist_exists_bool(nvl, "nvlist/bool/false"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number/0"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number/1"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number/-1"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number/UINT64_MAX"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number/INT64_MIN"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number/INT64_MAX"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string/"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string/x"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_exists_string(nvl, "nvlist/stringf/"));
	CHECK(nvlist_exists_string(nvl, "nvlist/stringf/x"));
	CHECK(nvlist_exists_string(nvl, "nvlist/stringf/666Xabc"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary/x"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));

	cnvl = nvlist_get_nvlist(nvl, "nvlist/nvlist");
	CHECK(nvlist_exists_null(cnvl, "nvlist/null"));
	CHECK(nvlist_exists_bool(cnvl, "nvlist/bool/true"));
	CHECK(nvlist_exists_bool(cnvl, "nvlist/bool/false"));
	CHECK(nvlist_exists_number(cnvl, "nvlist/number/0"));
	CHECK(nvlist_exists_number(cnvl, "nvlist/number/1"));
	CHECK(nvlist_exists_number(cnvl, "nvlist/number/-1"));
	CHECK(nvlist_exists_number(cnvl, "nvlist/number/UINT64_MAX"));
	CHECK(nvlist_exists_number(cnvl, "nvlist/number/INT64_MIN"));
	CHECK(nvlist_exists_number(cnvl, "nvlist/number/INT64_MAX"));
	CHECK(nvlist_exists_string(cnvl, "nvlist/string/"));
	CHECK(nvlist_exists_string(cnvl, "nvlist/string/x"));
	CHECK(nvlist_exists_string(cnvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_exists_string(cnvl, "nvlist/stringf/"));
	CHECK(nvlist_exists_string(cnvl, "nvlist/stringf/x"));
	CHECK(nvlist_exists_string(cnvl, "nvlist/stringf/666Xabc"));
	CHECK(nvlist_exists_descriptor(cnvl, "nvlist/descriptor/STDERR_FILENO"));
	CHECK(nvlist_exists_binary(cnvl, "nvlist/binary/x"));
	CHECK(nvlist_exists_binary(cnvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));

	nvlist_destroy(nvl);

	return (0);
}