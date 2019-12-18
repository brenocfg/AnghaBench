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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  member_0; } ;
struct file_info {int /*<<< orphan*/  name; int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void map_file(struct file_info *finfo)
{
    struct stat file_stat = {0};
    int fd;

    fd = open(finfo->name, O_RDONLY, (mode_t)0600);
    if (fd == -1) {
        ERR("Error while opening file %s.", finfo->name);
        exit(EXIT_FAILURE);
    }

    if (fstat(fd, &file_stat) == -1) {
        ERR("Error getting file size for %s.", finfo->name);
        exit(EXIT_FAILURE);
    }

    finfo->size = file_stat.st_size;
    finfo->data = mmap(0, finfo->size, PROT_READ, MAP_SHARED, fd, 0);

    if (finfo->data == MAP_FAILED) {
        ERR("Error mapping file %s.", finfo->name);
        exit(EXIT_FAILURE);
    }

    close(fd);
}