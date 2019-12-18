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
struct sparse {scalar_t__ type; size_t size; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 scalar_t__ END ; 
 scalar_t__ HOLE ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int ftruncate (int,size_t) ; 
 scalar_t__ lseek (int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int open (char const*,int,int) ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static void
create_sparse_file(const char *path, const struct sparse *s)
{
	char buff[1024];
	int fd;
	size_t total_size = 0;
	const struct sparse *cur = s;

	memset(buff, ' ', sizeof(buff));
	assert((fd = open(path, O_CREAT | O_WRONLY, 0600)) != -1);

	/* Handle holes at the end by extending the file */
	while (cur->type != END) {
		total_size += cur->size;
		++cur;
	}
	assert(ftruncate(fd, total_size) != -1);

	while (s->type != END) {
		if (s->type == HOLE) {
			assert(lseek(fd, s->size, SEEK_CUR) != (off_t)-1);
		} else {
			size_t w, size;

			size = s->size;
			while (size) {
				if (size > sizeof(buff))
					w = sizeof(buff);
				else
					w = size;
				assert(write(fd, buff, w) != (ssize_t)-1);
				size -= w;
			}
		}
		s++;
	}
	close(fd);
}