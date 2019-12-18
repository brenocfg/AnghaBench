#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct statfs {int f_flags; char* f_mntonname; } ;
struct stat {int dummy; } ;
struct TYPE_10__ {char* path; int mapsize; int dlopened; int /*<<< orphan*/  mapbase; scalar_t__ textrel; int /*<<< orphan*/  stack_flags; scalar_t__ z_noopen; int /*<<< orphan*/  dynsymcount; int /*<<< orphan*/  valid_hash_gnu; int /*<<< orphan*/  valid_hash_sysv; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UTRACE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int MNT_NOEXEC ; 
 int RTLD_LO_DLOPEN ; 
 int RTLD_LO_TRACE ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTRACE_LOAD_OBJECT ; 
 int /*<<< orphan*/  _rtld_error (char*,char*) ; 
 scalar_t__ dangerous_ld_env ; 
 int /*<<< orphan*/  dbg (char*,char*,...) ; 
 int /*<<< orphan*/  digest_dynamic (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fstatfs (int,struct statfs*) ; 
 int /*<<< orphan*/  linkmap_add (TYPE_1__*) ; 
 TYPE_1__* map_object (int,char*,struct stat*) ; 
 int /*<<< orphan*/  max_stack_flags ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  obj_count ; 
 int /*<<< orphan*/  obj_free (TYPE_1__*) ; 
 int /*<<< orphan*/  obj_list ; 
 int /*<<< orphan*/  obj_loads ; 
 int /*<<< orphan*/  object_add_name (TYPE_1__*,char const*) ; 
 char* printable_path (char*) ; 

__attribute__((used)) static Obj_Entry *
do_load_object(int fd, const char *name, char *path, struct stat *sbp,
  int flags)
{
    Obj_Entry *obj;
    struct statfs fs;

    /*
     * but first, make sure that environment variables haven't been
     * used to circumvent the noexec flag on a filesystem.
     */
    if (dangerous_ld_env) {
	if (fstatfs(fd, &fs) != 0) {
	    _rtld_error("Cannot fstatfs \"%s\"", printable_path(path));
	    return NULL;
	}
	if (fs.f_flags & MNT_NOEXEC) {
	    _rtld_error("Cannot execute objects on %s", fs.f_mntonname);
	    return NULL;
	}
    }
    dbg("loading \"%s\"", printable_path(path));
    obj = map_object(fd, printable_path(path), sbp);
    if (obj == NULL)
        return NULL;

    /*
     * If DT_SONAME is present in the object, digest_dynamic2 already
     * added it to the object names.
     */
    if (name != NULL)
	object_add_name(obj, name);
    obj->path = path;
    digest_dynamic(obj, 0);
    dbg("%s valid_hash_sysv %d valid_hash_gnu %d dynsymcount %d", obj->path,
	obj->valid_hash_sysv, obj->valid_hash_gnu, obj->dynsymcount);
    if (obj->z_noopen && (flags & (RTLD_LO_DLOPEN | RTLD_LO_TRACE)) ==
      RTLD_LO_DLOPEN) {
	dbg("refusing to load non-loadable \"%s\"", obj->path);
	_rtld_error("Cannot dlopen non-loadable %s", obj->path);
	munmap(obj->mapbase, obj->mapsize);
	obj_free(obj);
	return (NULL);
    }

    obj->dlopened = (flags & RTLD_LO_DLOPEN) != 0;
    TAILQ_INSERT_TAIL(&obj_list, obj, next);
    obj_count++;
    obj_loads++;
    linkmap_add(obj);	/* for GDB & dlinfo() */
    max_stack_flags |= obj->stack_flags;

    dbg("  %p .. %p: %s", obj->mapbase,
         obj->mapbase + obj->mapsize - 1, obj->path);
    if (obj->textrel)
	dbg("  WARNING: %s has impure text", obj->path);
    LD_UTRACE(UTRACE_LOAD_OBJECT, obj, obj->mapbase, obj->mapsize, 0,
	obj->path);    

    return obj;
}