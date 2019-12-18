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
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  nvlist_append_bool_array (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvlist_append_nvlist_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_append_string_array (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_error (int /*<<< orphan*/ *) ; 
 int nvlist_exists_bool_array (int /*<<< orphan*/ *,char*) ; 
 int* nvlist_get_bool_array (int /*<<< orphan*/ *,char*,size_t*) ; 
 int nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ ** nvlist_get_nvlist_array (int /*<<< orphan*/ *,char*,size_t*) ; 
 char const* const nvlist_get_string (int /*<<< orphan*/  const* const,char*) ; 
 char** nvlist_get_string_array (int /*<<< orphan*/ *,char*,size_t*) ; 
 int /*<<< orphan*/  nvlist_move_nvlist_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/ ** nvlist_take_nvlist_array (int /*<<< orphan*/ *,char*,size_t*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char const* const,char*) ; 

int
main(void)
{
	const bool *bool_result;
	const char * const *string_result;
	const nvlist_t * const *nvl_result;
	nvlist_t *nvl, *nvl1, *nvl2, **items;
	unsigned int i;
	size_t nitems;

	printf("1..32\n");

	nvl = nvlist_create(0);

	for (i = 0; i < 16; i++)
		nvlist_append_bool_array(nvl, "nvl/bool", i % 2 == 0);

	CHECK(nvlist_error(nvl) == 0);
	CHECK(!nvlist_empty(nvl));
	CHECK(nvlist_exists_bool_array(nvl, "nvl/bool"));

	bool_result = nvlist_get_bool_array(nvl, "nvl/bool", &nitems);
	CHECK(nitems == 16);
	CHECK(bool_result != NULL);
	for (i = 0; i < nitems; i++)
		CHECK(bool_result[i] == (i % 2 == 0));


	nvlist_append_string_array(nvl, "nvl/string", "a");
	nvlist_append_string_array(nvl, "nvl/string", "abc");
	string_result = nvlist_get_string_array(nvl, "nvl/string", &nitems);
	CHECK(nitems == 2);
	CHECK(strcmp(string_result[0], "a") == 0);
	CHECK(strcmp(string_result[1], "abc") == 0);


	nvl1 = nvlist_create(0);
	nvlist_add_string(nvl1, "key1", "test1");
	nvlist_append_nvlist_array(nvl, "nvl/nvl", nvl1);
	nvlist_destroy(nvl1);

	nvl2 = nvlist_create(0);
	nvlist_add_string(nvl2, "key2", "test2");
	nvlist_append_nvlist_array(nvl, "nvl/nvl", nvl2);
	nvlist_destroy(nvl2);

	nvl_result = nvlist_get_nvlist_array(nvl, "nvl/nvl", &nitems);
	CHECK(nitems == 2);
	CHECK(strcmp(nvlist_get_string(nvl_result[0], "key1"), "test1") == 0);
	CHECK(strcmp(nvlist_get_string(nvl_result[1], "key2"), "test2") == 0);

	nvl1 = nvlist_create(0);
	nvlist_add_number(nvl1, "key1", 10);
	nvlist_append_nvlist_array(nvl, "nvl/nvl_array", nvl1);
	nvlist_destroy(nvl1);

	nvl2 = nvlist_create(0);
	nvlist_add_number(nvl2, "key1", 20);
	nvlist_append_nvlist_array(nvl, "nvl/nvl_array", nvl2);
	nvlist_destroy(nvl2);

	items = nvlist_take_nvlist_array(nvl, "nvl/nvl_array", &nitems);
	CHECK(nvlist_get_number(items[0], "key1") == 10);
	CHECK(nvlist_get_number(items[1], "key1") == 20);
	CHECK(nvlist_error(items[0]) == 0);
	CHECK(nvlist_error(items[1]) == 0);

	nvlist_move_nvlist_array(nvl, "nvl/nvl_new_array", items, nitems);
	CHECK(nvlist_error(nvl) == 0);

	nvlist_destroy(nvl);

	return (0);
}