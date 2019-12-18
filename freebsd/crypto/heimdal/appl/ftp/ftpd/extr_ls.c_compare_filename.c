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
struct fileinfo {int /*<<< orphan*/ * filename; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
compare_filename(struct fileinfo *a, struct fileinfo *b)
{
    if(a->filename == NULL)
	return 1;
    if(b->filename == NULL)
	return -1;
    return strcmp(a->filename, b->filename);
}