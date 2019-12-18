#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* entryaddr; void* memaddr; void* baseaddr; void* part_size; void* data_size; void* index; int /*<<< orphan*/  name; int /*<<< orphan*/  magic; } ;
typedef  TYPE_2__ part_t ;
struct TYPE_6__ {int /*<<< orphan*/  st_size; } ;
struct TYPE_8__ {TYPE_1__ stats; int /*<<< orphan*/  partition_entryaddr; int /*<<< orphan*/  partition_memaddr; int /*<<< orphan*/  partition_baseaddr; int /*<<< orphan*/  partition_length; int /*<<< orphan*/  partition_index; int /*<<< orphan*/  partition_name; int /*<<< orphan*/  filename; } ;
typedef  TYPE_3__ part_data_t ;
struct TYPE_9__ {long pad; void* crc; } ;
typedef  TYPE_4__ part_crc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*,int /*<<< orphan*/ ) ; 
 int MAGIC_LENGTH ; 
 int /*<<< orphan*/  MAGIC_PART ; 
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  crc32 (long,void*,int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_part(void* mem, part_data_t* d)
{
	char* addr;
	int fd;
	part_t* p = mem;
	part_crc_t* crc = mem + sizeof(part_t) + d->stats.st_size;

	fd = open(d->filename, O_RDONLY);
	if (fd < 0)
	{
		ERROR("Failed opening file '%s'\n", d->filename);
		return -1;
	}

	if ((addr=(char*)mmap(0, d->stats.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
	{
		ERROR("Failed mmaping memory for file '%s'\n", d->filename);
		close(fd);
		return -2;
	}

	memcpy(mem + sizeof(part_t), addr, d->stats.st_size);
	munmap(addr, d->stats.st_size);

	memset(p->name, 0, sizeof(p->name));
	strncpy(p->magic, MAGIC_PART, MAGIC_LENGTH);
	strncpy(p->name, d->partition_name, sizeof(p->name));
	p->index = htonl(d->partition_index);
	p->data_size = htonl(d->stats.st_size);
	p->part_size = htonl(d->partition_length);
	p->baseaddr = htonl(d->partition_baseaddr);
	p->memaddr = htonl(d->partition_memaddr);
	p->entryaddr = htonl(d->partition_entryaddr);

	crc->crc = htonl(crc32(0L, mem, d->stats.st_size + sizeof(part_t)));
	crc->pad = 0L;

	return 0;
}