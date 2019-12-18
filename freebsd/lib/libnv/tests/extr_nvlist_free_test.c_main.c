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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_descriptor (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_null (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int nvlist_empty (int /*<<< orphan*/ *) ; 
 int nvlist_exists_binary (int /*<<< orphan*/ *,char*) ; 
 int nvlist_exists_bool (int /*<<< orphan*/ *,char*) ; 
 int nvlist_exists_descriptor (int /*<<< orphan*/ *,char*) ; 
 int nvlist_exists_null (int /*<<< orphan*/ *,char*) ; 
 int nvlist_exists_number (int /*<<< orphan*/ *,char*) ; 
 int nvlist_exists_nvlist (int /*<<< orphan*/ *,char*) ; 
 int nvlist_exists_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free_binary (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free_descriptor (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free_null (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free_number (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free_nvlist (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
main(void)
{
	nvlist_t *nvl;

	printf("1..114\n");

	nvl = nvlist_create(0);

	nvlist_add_null(nvl, "nvlist/null");
	nvlist_add_bool(nvl, "nvlist/bool", true);
	nvlist_add_number(nvl, "nvlist/number", 0);
	nvlist_add_string(nvl, "nvlist/string", "test");
	nvlist_add_nvlist(nvl, "nvlist/nvlist", nvl);
	nvlist_add_descriptor(nvl, "nvlist/descriptor", STDERR_FILENO);
	nvlist_add_binary(nvl, "nvlist/binary", "test", 4);

	CHECK(nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free_null(nvl, "nvlist/null");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free_bool(nvl, "nvlist/bool");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free_number(nvl, "nvlist/number");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free_string(nvl, "nvlist/string");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(!nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free_nvlist(nvl, "nvlist/nvlist");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(!nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free_descriptor(nvl, "nvlist/descriptor");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(!nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(!nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free_binary(nvl, "nvlist/binary");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(!nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(!nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(!nvlist_exists_binary(nvl, "nvlist/binary"));

	CHECK(nvlist_empty(nvl));

	nvlist_add_null(nvl, "nvlist/null");
	nvlist_add_bool(nvl, "nvlist/bool", true);
	nvlist_add_number(nvl, "nvlist/number", 0);
	nvlist_add_string(nvl, "nvlist/string", "test");
	nvlist_add_nvlist(nvl, "nvlist/nvlist", nvl);
	nvlist_add_descriptor(nvl, "nvlist/descriptor", STDERR_FILENO);
	nvlist_add_binary(nvl, "nvlist/binary", "test", 4);

	CHECK(nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free(nvl, "nvlist/null");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free(nvl, "nvlist/bool");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free(nvl, "nvlist/number");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free(nvl, "nvlist/string");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(!nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free(nvl, "nvlist/nvlist");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(!nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free(nvl, "nvlist/descriptor");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(!nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(!nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary"));

	nvlist_free(nvl, "nvlist/binary");
	CHECK(!nvlist_exists_null(nvl, "nvlist/null"));
	CHECK(!nvlist_exists_bool(nvl, "nvlist/bool"));
	CHECK(!nvlist_exists_number(nvl, "nvlist/number"));
	CHECK(!nvlist_exists_string(nvl, "nvlist/string"));
	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(!nvlist_exists_descriptor(nvl, "nvlist/descriptor"));
	CHECK(!nvlist_exists_binary(nvl, "nvlist/binary"));

	CHECK(nvlist_empty(nvl));

	nvlist_destroy(nvl);

	return (0);
}