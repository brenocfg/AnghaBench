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
struct split_file {int curfd; size_t curfile; char** descsv; scalar_t__ file_pos; int /*<<< orphan*/ * filesv; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ENOENT ; 
 int NTRIES ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getchar () ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static int
split_openfile(struct split_file *sf)
{
    int i;

    for (i = 0;; i++) {
	sf->curfd = open(sf->filesv[sf->curfile], O_RDONLY);
	if (sf->curfd >= 0)
	    break;
	if ((sf->curfd == -1) && (errno != ENOENT))
	    return (errno);
	if (i == NTRIES)
	    return (EIO);
	printf("\nInsert disk labelled %s and press any key...",
	    sf->descsv[sf->curfile]);
	getchar();
	putchar('\n');
    }
    sf->file_pos = 0;
    return (0);
}