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
struct string_list_item {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repack ; 

__attribute__((used)) static int keep_one_pack(struct string_list_item *item, void *data)
{
	argv_array_pushf(&repack, "--keep-pack=%s", basename(item->string));
	return 0;
}