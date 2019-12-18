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
struct rerere_dir {int /*<<< orphan*/ * status; int /*<<< orphan*/  hash; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  RR_HAS_POSTIMAGE ; 
 int /*<<< orphan*/  RR_HAS_PREIMAGE ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fit_variant (struct rerere_dir*,int) ; 
 int /*<<< orphan*/  git_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_to_hex (int /*<<< orphan*/ ) ; 
 scalar_t__ is_rr_file (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scan_rerere_dir(struct rerere_dir *rr_dir)
{
	struct dirent *de;
	DIR *dir = opendir(git_path("rr-cache/%s", hash_to_hex(rr_dir->hash)));

	if (!dir)
		return;
	while ((de = readdir(dir)) != NULL) {
		int variant;

		if (is_rr_file(de->d_name, "postimage", &variant)) {
			fit_variant(rr_dir, variant);
			rr_dir->status[variant] |= RR_HAS_POSTIMAGE;
		} else if (is_rr_file(de->d_name, "preimage", &variant)) {
			fit_variant(rr_dir, variant);
			rr_dir->status[variant] |= RR_HAS_PREIMAGE;
		}
	}
	closedir(dir);
}