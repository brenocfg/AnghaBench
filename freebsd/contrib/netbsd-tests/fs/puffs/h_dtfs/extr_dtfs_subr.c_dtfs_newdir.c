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
struct dtfs_file {int /*<<< orphan*/  df_dirents; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 struct dtfs_file* emalloc (int) ; 
 int /*<<< orphan*/  memset (struct dtfs_file*,int /*<<< orphan*/ ,int) ; 

struct dtfs_file *
dtfs_newdir()
{
	struct dtfs_file *dff;

	dff = emalloc(sizeof(struct dtfs_file));
	memset(dff, 0, sizeof(struct dtfs_file));
	LIST_INIT(&dff->df_dirents);

	return dff;
}