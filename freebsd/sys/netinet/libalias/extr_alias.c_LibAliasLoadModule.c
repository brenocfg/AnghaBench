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
struct proto_handler {int dummy; } ;
struct dll {void* handle; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ moduledata_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLL_LEN ; 
 scalar_t__ EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LibAliasAttachHandlers (struct proto_handler*) ; 
 int /*<<< orphan*/  RTLD_LAZY ; 
 scalar_t__ attach_dll (struct dll*) ; 
 char* dlerror () ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct dll*) ; 
 struct dll* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
LibAliasLoadModule(char *path)
{
	struct dll *t;
	void *handle;
	struct proto_handler *m;
        const char *error;
	moduledata_t *p;

        handle = dlopen (path, RTLD_LAZY);
        if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		return (EINVAL);
        }

	p = dlsym(handle, "alias_mod");
        if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "%s\n", dlerror());
		return (EINVAL);
        }

	t = malloc(sizeof(struct dll));
	if (t == NULL)
		return (ENOMEM);
	strncpy(t->name, p->name, DLL_LEN);
	t->handle = handle;
	if (attach_dll(t) == EEXIST) {
		free(t);
		fprintf(stderr, "dll conflict\n");
		return (EEXIST);
	}

        m = dlsym(t->handle, "handlers");
        if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "%s\n", error);
		return (EINVAL);
	}

	LibAliasAttachHandlers(m);
	return (0);
}