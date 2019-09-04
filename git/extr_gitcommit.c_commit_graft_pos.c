#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct repository {TYPE_1__* parsed_objects; } ;
struct TYPE_2__ {int /*<<< orphan*/  grafts_nr; int /*<<< orphan*/  grafts; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_graft_sha1_access ; 
 int sha1_pos (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int commit_graft_pos(struct repository *r, const unsigned char *sha1)
{
	return sha1_pos(sha1, r->parsed_objects->grafts,
			r->parsed_objects->grafts_nr,
			commit_graft_sha1_access);
}