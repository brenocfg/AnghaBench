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
struct untracked_cache_dir {int valid; int /*<<< orphan*/  stat_data; } ;
struct stat_data {int dummy; } ;
struct read_data {scalar_t__ data; scalar_t__ end; struct untracked_cache_dir** ucd; } ;

/* Variables and functions */
 int /*<<< orphan*/  stat_data_from_disk (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void read_stat(size_t pos, void *cb)
{
	struct read_data *rd = cb;
	struct untracked_cache_dir *ud = rd->ucd[pos];
	if (rd->data + sizeof(struct stat_data) > rd->end) {
		rd->data = rd->end + 1;
		return;
	}
	stat_data_from_disk(&ud->stat_data, rd->data);
	rd->data += sizeof(struct stat_data);
	ud->valid = 1;
}