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
 int /*<<< orphan*/  STDERR_FILENO ; 
 int dup (int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 void* nvlist_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/  const*) ; 
 scalar_t__ nvlist_error (int /*<<< orphan*/  const*) ; 
 int nvlist_exists_binary (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_descriptor (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_nvlist (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_exists_string (int /*<<< orphan*/  const*,char*) ; 
 void* nvlist_get_binary (int /*<<< orphan*/  const*,char*,size_t*) ; 
 int nvlist_get_descriptor (int /*<<< orphan*/  const*,char*) ; 
 void* nvlist_get_nvlist (int /*<<< orphan*/  const*,char*) ; 
 void* nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_move_binary (int /*<<< orphan*/  const*,char*,void*,int) ; 
 int /*<<< orphan*/  nvlist_move_descriptor (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  nvlist_move_nvlist (int /*<<< orphan*/  const*,char*,void*) ; 
 int /*<<< orphan*/  nvlist_move_string (int /*<<< orphan*/  const*,char*,void*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* strdup (char*) ; 

int
main(void)
{
	const nvlist_t *cnvl;
	nvlist_t *nvl;
	void *ptr;
	size_t size;
	int fd;

	printf("1..52\n");

	nvl = nvlist_create(0);

	CHECK(!nvlist_exists_string(nvl, "nvlist/string/"));
	ptr = strdup("");
	CHECK(ptr != NULL);
	nvlist_move_string(nvl, "nvlist/string/", ptr);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl, "nvlist/string/"));
	CHECK(ptr == nvlist_get_string(nvl, "nvlist/string/"));

	CHECK(!nvlist_exists_string(nvl, "nvlist/string/x"));
	ptr = strdup("x");
	CHECK(ptr != NULL);
	nvlist_move_string(nvl, "nvlist/string/x", ptr);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl, "nvlist/string/x"));
	CHECK(ptr == nvlist_get_string(nvl, "nvlist/string/x"));

	CHECK(!nvlist_exists_string(nvl,
	    "nvlist/string/abcdefghijklmnopqrstuvwxyz"));
	ptr = strdup("abcdefghijklmnopqrstuvwxyz");
	CHECK(ptr != NULL);
	nvlist_move_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz",
	    ptr);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_string(nvl,
	    "nvlist/string/abcdefghijklmnopqrstuvwxyz"));
	CHECK(ptr ==
	    nvlist_get_string(nvl, "nvlist/string/abcdefghijklmnopqrstuvwxyz"));

	CHECK(!nvlist_exists_descriptor(nvl,
	    "nvlist/descriptor/STDERR_FILENO"));
	fd = dup(STDERR_FILENO);
	CHECK(fd >= 0);
	nvlist_move_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO", fd);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO"));
	CHECK(fd ==
	    nvlist_get_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO"));

	CHECK(!nvlist_exists_binary(nvl, "nvlist/binary/x"));
	ptr = malloc(1);
	CHECK(ptr != NULL);
	memcpy(ptr, "x", 1);
	nvlist_move_binary(nvl, "nvlist/binary/x", ptr, 1);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary/x"));
	CHECK(ptr == nvlist_get_binary(nvl, "nvlist/binary/x", NULL));
	CHECK(ptr == nvlist_get_binary(nvl, "nvlist/binary/x", &size));
	CHECK(size == 1);

	CHECK(!nvlist_exists_binary(nvl,
	    "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));
	ptr = malloc(sizeof("abcdefghijklmnopqrstuvwxyz"));
	CHECK(ptr != NULL);
	memcpy(ptr, "abcdefghijklmnopqrstuvwxyz",
	    sizeof("abcdefghijklmnopqrstuvwxyz"));
	nvlist_move_binary(nvl, "nvlist/binary/abcdefghijklmnopqrstuvwxyz",
	    ptr, sizeof("abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_binary(nvl,
	    "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));
	CHECK(ptr == nvlist_get_binary(nvl,
	    "nvlist/binary/abcdefghijklmnopqrstuvwxyz", NULL));
	CHECK(ptr == nvlist_get_binary(nvl,
	    "nvlist/binary/abcdefghijklmnopqrstuvwxyz", &size));
	CHECK(size == sizeof("abcdefghijklmnopqrstuvwxyz"));

	CHECK(!nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	ptr = nvlist_clone(nvl);
	CHECK(ptr != NULL);
	nvlist_move_nvlist(nvl, "nvlist/nvlist", ptr);
	CHECK(nvlist_error(nvl) == 0);
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));
	CHECK(ptr == nvlist_get_nvlist(nvl, "nvlist/nvlist"));

	CHECK(nvlist_exists_string(nvl, "nvlist/string/"));
	CHECK(nvlist_exists_string(nvl, "nvlist/string/x"));
	CHECK(nvlist_exists_string(nvl,
	    "nvlist/string/abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_exists_descriptor(nvl, "nvlist/descriptor/STDERR_FILENO"));
	CHECK(nvlist_exists_binary(nvl, "nvlist/binary/x"));
	CHECK(nvlist_exists_binary(nvl,
	    "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_exists_nvlist(nvl, "nvlist/nvlist"));

	cnvl = nvlist_get_nvlist(nvl, "nvlist/nvlist");
	CHECK(nvlist_exists_string(cnvl, "nvlist/string/"));
	CHECK(nvlist_exists_string(cnvl, "nvlist/string/x"));
	CHECK(nvlist_exists_string(cnvl,
	    "nvlist/string/abcdefghijklmnopqrstuvwxyz"));
	CHECK(nvlist_exists_descriptor(cnvl,
	    "nvlist/descriptor/STDERR_FILENO"));
	CHECK(nvlist_exists_binary(cnvl, "nvlist/binary/x"));
	CHECK(nvlist_exists_binary(cnvl,
	    "nvlist/binary/abcdefghijklmnopqrstuvwxyz"));

	nvlist_destroy(nvl);

	return (0);
}