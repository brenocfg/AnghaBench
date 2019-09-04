#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct index_extension {int /*<<< orphan*/  extension_size; } ;
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_3__ {int size; struct index_extension* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int git_filebuf_write (int /*<<< orphan*/ *,struct index_extension*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct index_extension*,struct index_extension*,int) ; 
 int /*<<< orphan*/  memset (struct index_extension*,int,int) ; 

__attribute__((used)) static int write_extension(git_filebuf *file, struct index_extension *header, git_buf *data)
{
	struct index_extension ondisk;

	memset(&ondisk, 0x0, sizeof(struct index_extension));
	memcpy(&ondisk, header, 4);
	ondisk.extension_size = htonl(header->extension_size);

	git_filebuf_write(file, &ondisk, sizeof(struct index_extension));
	return git_filebuf_write(file, data->ptr, data->size);
}