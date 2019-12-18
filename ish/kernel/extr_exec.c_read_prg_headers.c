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
struct prg_header {int dummy; } ;
struct fd {TYPE_1__* ops; } ;
struct elf_header {int phent_count; int /*<<< orphan*/  prghead_off; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ (* lseek ) (struct fd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read ) (struct fd*,struct prg_header*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int _EIO ; 
 int _ENOEXEC ; 
 int _ENOMEM ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct prg_header*) ; 
 struct prg_header* malloc (scalar_t__) ; 
 scalar_t__ stub1 (struct fd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct fd*,struct prg_header*,scalar_t__) ; 

__attribute__((used)) static int read_prg_headers(struct fd *fd, struct elf_header header, struct prg_header **ph_out) {
    ssize_t ph_size = sizeof(struct prg_header) * header.phent_count;
    struct prg_header *ph = malloc(ph_size);
    if (ph == NULL)
        return _ENOMEM;

    if (fd->ops->lseek(fd, header.prghead_off, SEEK_SET) < 0) {
        free(ph);
        return _EIO;
    }
    if (fd->ops->read(fd, ph, ph_size) != ph_size) {
        free(ph);
        if (errno != 0)
            return _EIO;
        return _ENOEXEC;
    }

    *ph_out = ph;
    return 0;
}