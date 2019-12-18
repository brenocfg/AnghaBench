#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* linker_file_t ;
typedef  scalar_t__ linker_class_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
struct TYPE_4__ {int refs; int /*<<< orphan*/  modules; int /*<<< orphan*/  common; scalar_t__ loadcnt; int /*<<< orphan*/ * deps; scalar_t__ ndeps; int /*<<< orphan*/  id; void* pathname; void* filename; scalar_t__ flags; scalar_t__ userrefs; scalar_t__ ctors_size; scalar_t__ ctors_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE ; 
 int /*<<< orphan*/  KLD_DPF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LINKER_GET_NEXT_FILE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LINKER ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/  kld_sx ; 
 scalar_t__ kobj_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 char* linker_basename (char const*) ; 
 int /*<<< orphan*/  linker_files ; 
 scalar_t__ loadcnt ; 
 void* strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

linker_file_t
linker_make_file(const char *pathname, linker_class_t lc)
{
	linker_file_t lf;
	const char *filename;

	if (!cold)
		sx_assert(&kld_sx, SA_XLOCKED);
	filename = linker_basename(pathname);

	KLD_DPF(FILE, ("linker_make_file: new file, filename='%s' for pathname='%s'\n", filename, pathname));
	lf = (linker_file_t)kobj_create((kobj_class_t)lc, M_LINKER, M_WAITOK);
	if (lf == NULL)
		return (NULL);
	lf->ctors_addr = 0;
	lf->ctors_size = 0;
	lf->refs = 1;
	lf->userrefs = 0;
	lf->flags = 0;
	lf->filename = strdup(filename, M_LINKER);
	lf->pathname = strdup(pathname, M_LINKER);
	LINKER_GET_NEXT_FILE_ID(lf->id);
	lf->ndeps = 0;
	lf->deps = NULL;
	lf->loadcnt = ++loadcnt;
	STAILQ_INIT(&lf->common);
	TAILQ_INIT(&lf->modules);
	TAILQ_INSERT_TAIL(&linker_files, lf, link);
	return (lf);
}