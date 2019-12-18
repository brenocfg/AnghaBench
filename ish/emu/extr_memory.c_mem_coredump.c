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
struct pt_entry {TYPE_1__* data; } ;
struct mem {int dummy; } ;
typedef  int page_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int MEM_PAGES ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PAGE_BITS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ftruncate (int,int) ; 
 scalar_t__ lseek (int,int,int /*<<< orphan*/ ) ; 
 struct pt_entry* mem_pt (struct mem*,int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mem_coredump(struct mem *mem, const char *file) {
    int fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        return;
    }
    if (ftruncate(fd, 0xffffffff) < 0) {
        perror("ftruncate");
        return;
    }

    int pages = 0;
    for (page_t page = 0; page < MEM_PAGES; page++) {
        struct pt_entry *entry = mem_pt(mem, page);
        if (entry == NULL)
            continue;
        pages++;
        if (lseek(fd, page << PAGE_BITS, SEEK_SET) < 0) {
            perror("lseek");
            return;
        }
        if (write(fd, entry->data->data, PAGE_SIZE) < 0) {
            perror("write");
            return;
        }
    }
    printk("dumped %d pages\n", pages);
    close(fd);
}