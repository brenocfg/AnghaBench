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
struct file_reader {scalar_t__ file; scalar_t__ fname; scalar_t__ buffer; scalar_t__ fd; int /*<<< orphan*/  mmapsize; scalar_t__ mmapaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  closefile (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct file_reader*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_free (scalar_t__) ; 
 scalar_t__ stdin ; 

__attribute__((used)) static void
file_reader_clean(struct file_reader *fr)
{

	if (fr) {
		if (fr->mmapaddr)
			munmap(fr->mmapaddr, fr->mmapsize);

		if (fr->fd)
			close(fr->fd);

		if (fr->buffer)
			sort_free(fr->buffer);

		if (fr->file)
			if (fr->file != stdin)
				closefile(fr->file, fr->fname);

		if(fr->fname)
			sort_free(fr->fname);

		memset(fr, 0, sizeof(struct file_reader));
	}
}