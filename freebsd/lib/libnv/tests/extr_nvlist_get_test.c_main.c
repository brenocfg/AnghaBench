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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int INT64_MAX ; 
 int INT64_MIN ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int UINT64_MAX ; 
 int fd_is_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/  const*,char*,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_bool (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_descriptor (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/  const*,char*,char*) ; 
 int /*<<< orphan*/  const* nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/  const*) ; 
 scalar_t__ nvlist_error (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvlist_exists_binary (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_exists_bool (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_exists_descriptor (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_exists_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_exists_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_binary (int /*<<< orphan*/  const*,char*,size_t*) ; 
 int nvlist_get_bool (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_descriptor (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* nvlist_get_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
main(void)
{
	const nvlist_t *cnvl;
	nvlist_t *nvl;
	size_t size;

	printf("1..83\n");

	nvl = nvlist_create(0);

	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool/true"));
	nvlist_add_bool(nvl, "nvlist/bool/true", true);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_get_bool(nvl, "nvlist/bool/true") == true);

	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool/false"));
	nvlist_add_bool(nvl, "nvlist/bool/false", false);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_get_bool(nvl, "nvlist/bool/false") == false);

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/0"));
	nvlist_add_number(nvl, "nvlist/number/0", 0);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_get_number(nvl, "nvlist/number/0") == 0);

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/1"));
	nvlist_add_number(nvl, "nvlist/number/1", 1);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_get_number(nvl, "nvlist/number/1") == 1);

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/-1"));
	nvlist_add_number(nvl, "nvlist/number/-1", -1);
	CHECK(nvlist_error(nvl) == 0);
	CHECK((int)nvlist_get_number(nvl, "nvlist/number/-1") == -1);

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/UINT64_MAX"));
	nvlist_add_number(nvl, "nvlist/number/UINT64_MAX", UINT64_MAX);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_get_number(nvl, "nvlist/number/UINT64_MAX") == UINT64_MAX);

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/INT64_MIN"));
	nvlist_add_number(nvl, "nvlist/number/INT64_MIN", INT64_MIN);
	CHECK(nvlist_error(nvl) == 0);
	CHECK((int64_t)nvlist_get_number(nvl, "nvlist/number/INT64_MIN") == INT64_MIN);

	CHECK(!nvlist_exists_number(nvl, "nvlist/number/INT64_MAX"));
	nvlist_add_number(nvl, "nvlist/number/INT64_MAX", INT64_MAX);
	CHECK(nvlist_error(nvl) == 0);
	CHECK((int64_t)nvlist_get_number(nvl, "nvlist/number/INT64_MAX") == INT64_MAX);

	CHECK(!nvlist_exists_string(nvl, "nvlist/string/"));
	nvlist_add_string(nvl, "nvlist/string/", "");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(strcmp(nvlist_get_string(nvl, "nvlist/string/"), "") == 0);

	CHECK(!nvlist_exists_string(nvl, "nvlist/string/x"));
	nvlist_add_string(nvl, "nvlist/string/x", "x");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(strcmp(nvlist_get_string(nvl, "nvlist/string/x"), "x") == 0);

	CHECK(!nvlist_exists_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"));
	nvlist_add_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
	CHECK(nvlist_error(nvl) == 0);
	CHECK(strcmp(nvlist_get_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz") == 0);

	CHECK(!nvlist_exists_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO"));
	nvlist_add_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO", STDERR_FILENO);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(fd_is_valid(nvlist_get_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO")));

	CHECK(!nvlist_exists_binary(nvl, "nvlist/binary/x"));
	nvlist_add_binary(nvl, "nvlist/binary/x", "x", 1);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(memcmp(nvlist_get_binary(nvl, "nvlist/binary/x", NULL), "x", 1) == 0);
	CHECK(memcmp(nvlist_get_binary(nvl, "nvlist/binary/x", &size), "x", 1) == 0);
	CHECK(size == 1);

	CHECK(!nvlist_exists_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));
	nvlist_add_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", sizeof("abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_error(nvl) == 0);
	CHECK(memcmp(nvlist_get_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz", NULL), "abcdefghijklmnopqrstuvwxyz", sizeof("abcdefghijklmnopqrstuvwxyz")) == 0);
	CHECK(memcmp(nvlist_get_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz", &size), "abcdefghijklmnopqrstuvwxyz", sizeof("abcdefghijklmnopqrstuvwxyz")) == 0);
	CHECK(size == sizeof("abcdefghijklmnopqrstuvwxyz"));

	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	nvlist_add_nvlist(nvl, "nvlist/nvlist", nvl);
	CHECK(nvlist_error(nvl) == 0);
	cnvl = nvlist_get_nvlist(nvl, "nvlist/nvlist");
	CHECK(nvlist_get_bool(cnvl, "nvlist/bool/true") == true);
	CHECK(nvlist_get_bool(cnvl, "nvlist/bool/false") == false);
	CHECK(nvlist_get_number(cnvl, "nvlist/number/0") == 0);
	CHECK(nvlist_get_number(cnvl, "nvlist/number/1") == 1);
	CHECK((int)nvlist_get_number(cnvl, "nvlist/number/-1") == -1);
	CHECK(nvlist_get_number(cnvl, "nvlist/number/UINT64_MAX") == UINT64_MAX);
	CHECK((int64_t)nvlist_get_number(cnvl, "nvlist/number/INT64_MIN") == INT64_MIN);
	CHECK((int64_t)nvlist_get_number(cnvl, "nvlist/number/INT64_MAX") == INT64_MAX);
	CHECK(strcmp(nvlist_get_string(cnvl, "nvlist/string/"), "") == 0);
	CHECK(strcmp(nvlist_get_string(cnvl, "nvlist/string/x"), "x") == 0);
	CHECK(strcmp(nvlist_get_string(cnvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz") == 0);
	/* TODO */
	CHECK(memcmp(nvlist_get_binary(cnvl, "nvlist/binary/x", NULL), "x", 1) == 0);
	CHECK(memcmp(nvlist_get_binary(cnvl, "nvlist/binary/x", &size), "x", 1) == 0);
	CHECK(size == 1);
	CHECK(memcmp(nvlist_get_binary(cnvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz", NULL), "abcdefghijklmnopqrstuvwxyz", sizeof("abcdefghijklmnopqrstuvwxyz")) == 0);
	CHECK(memcmp(nvlist_get_binary(cnvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz", &size), "abcdefghijklmnopqrstuvwxyz", sizeof("abcdefghijklmnopqrstuvwxyz")) == 0);
	CHECK(size == sizeof("abcdefghijklmnopqrstuvwxyz"));

	CHECK(nvlist_get_bool(nvl, "nvlist/bool/true") == true);
	CHECK(nvlist_get_bool(nvl, "nvlist/bool/false") == false);
	CHECK(nvlist_get_number(nvl, "nvlist/number/0") == 0);
	CHECK(nvlist_get_number(nvl, "nvlist/number/1") == 1);
	CHECK((int)nvlist_get_number(nvl, "nvlist/number/-1") == -1);
	CHECK(nvlist_get_number(nvl, "nvlist/number/UINT64_MAX") == UINT64_MAX);
	CHECK((int64_t)nvlist_get_number(nvl, "nvlist/number/INT64_MIN") == INT64_MIN);
	CHECK((int64_t)nvlist_get_number(nvl, "nvlist/number/INT64_MAX") == INT64_MAX);
	CHECK(strcmp(nvlist_get_string(nvl, "nvlist/string/"), "") == 0);
	CHECK(strcmp(nvlist_get_string(nvl, "nvlist/string/x"), "x") == 0);
	CHECK(strcmp(nvlist_get_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz") == 0);
	CHECK(fd_is_valid(nvlist_get_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO")));
	CHECK(memcmp(nvlist_get_binary(nvl, "nvlist/binary/x", NULL), "x", 1) == 0);
	CHECK(memcmp(nvlist_get_binary(nvl, "nvlist/binary/x", &size), "x", 1) == 0);
	CHECK(size == 1);
	CHECK(memcmp(nvlist_get_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz", NULL), "abcdefghijklmnopqrstuvwxyz", sizeof("abcdefghijklmnopqrstuvwxyz")) == 0);
	CHECK(memcmp(nvlist_get_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz", &size), "abcdefghijklmnopqrstuvwxyz", sizeof("abcdefghijklmnopqrstuvwxyz")) == 0);
	CHECK(size == sizeof("abcdefghijklmnopqrstuvwxyz"));

	nvlist_destroy(nvl);

	return (0);
}