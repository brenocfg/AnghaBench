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
struct fileinfo {int /*<<< orphan*/  link; int /*<<< orphan*/  filename; int /*<<< orphan*/  date; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  size; int /*<<< orphan*/  group; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_fileinfo(struct fileinfo *f)
{
    free(f->user);
    free(f->group);
    free(f->size);
    free(f->major);
    free(f->minor);
    free(f->date);
    free(f->filename);
    free(f->link);
}