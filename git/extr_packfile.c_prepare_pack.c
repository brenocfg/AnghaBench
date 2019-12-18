#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct prepare_pack_data {int /*<<< orphan*/  garbage; TYPE_2__* r; int /*<<< orphan*/  local; scalar_t__ m; } ;
struct packed_git {int /*<<< orphan*/  pack_name; struct packed_git* next; } ;
struct TYPE_4__ {TYPE_1__* objects; } ;
struct TYPE_3__ {struct packed_git* packed_git; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKDIR_FILE_GARBAGE ; 
 struct packed_git* add_packed_git (char const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ends_with (char const*,char*) ; 
 int /*<<< orphan*/  install_packed_git (TYPE_2__*,struct packed_git*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ midx_contains_pack (scalar_t__,char const*) ; 
 int /*<<< orphan*/  report_garbage (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strip_suffix (int /*<<< orphan*/ ,char*,size_t*) ; 
 scalar_t__ strip_suffix_mem (char const*,size_t*,char*) ; 

__attribute__((used)) static void prepare_pack(const char *full_name, size_t full_name_len,
			 const char *file_name, void *_data)
{
	struct prepare_pack_data *data = (struct prepare_pack_data *)_data;
	struct packed_git *p;
	size_t base_len = full_name_len;

	if (strip_suffix_mem(full_name, &base_len, ".idx") &&
	    !(data->m && midx_contains_pack(data->m, file_name))) {
		/* Don't reopen a pack we already have. */
		for (p = data->r->objects->packed_git; p; p = p->next) {
			size_t len;
			if (strip_suffix(p->pack_name, ".pack", &len) &&
			    len == base_len &&
			    !memcmp(p->pack_name, full_name, len))
				break;
		}

		if (!p) {
			p = add_packed_git(full_name, full_name_len, data->local);
			if (p)
				install_packed_git(data->r, p);
		}
	}

	if (!report_garbage)
		return;

	if (!strcmp(file_name, "multi-pack-index"))
		return;
	if (ends_with(file_name, ".idx") ||
	    ends_with(file_name, ".pack") ||
	    ends_with(file_name, ".bitmap") ||
	    ends_with(file_name, ".keep") ||
	    ends_with(file_name, ".promisor"))
		string_list_append(data->garbage, full_name);
	else
		report_garbage(PACKDIR_FILE_GARBAGE, full_name);
}