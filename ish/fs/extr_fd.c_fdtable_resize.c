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
struct fdtable {unsigned int size; struct fd** cloexec; struct fd** files; } ;
struct fd {int dummy; } ;
typedef  struct fd* bits_t ;

/* Variables and functions */
 int BITS_SIZE (unsigned int) ; 
 int _ENOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct fd**) ; 
 struct fd** malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct fd**,struct fd**,int) ; 
 int /*<<< orphan*/  memset (struct fd**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fdtable_resize(struct fdtable *table, unsigned size) {
    // currently the only legitimate use of this is to expand the table
    assert(size > table->size);

    struct fd **files = malloc(sizeof(struct fd *) * size);
    if (files == NULL)
        return _ENOMEM;
    memset(files, 0, sizeof(struct fd *) * size);
    if (table->files)
        memcpy(files, table->files, sizeof(struct fd *) * table->size);

    bits_t *cloexec = malloc(BITS_SIZE(size));
    if (cloexec == NULL) {
        free(files);
        return _ENOMEM;
    }
    memset(cloexec, 0, BITS_SIZE(size));
    if (table->cloexec)
        memcpy(cloexec, table->cloexec, BITS_SIZE(table->size));

    free(table->files);
    table->files = files;
    free(table->cloexec);
    table->cloexec = cloexec;
    table->size = size;
    return 0;
}