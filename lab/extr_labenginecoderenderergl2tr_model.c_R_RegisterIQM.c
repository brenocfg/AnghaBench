#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qhandle_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  index; void* type; } ;
typedef  TYPE_1__ model_t ;
struct TYPE_6__ {int (* FS_ReadFile ) (char const*,void**) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char const*) ;int /*<<< orphan*/  (* FS_FreeFile ) (void*) ;} ;

/* Variables and functions */
 void* MOD_BAD ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int /*<<< orphan*/  R_LoadIQM (TYPE_1__*,unsigned int*,int,char const*) ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_2__ ri ; 
 int stub1 (char const*,void**) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,char const*) ; 

qhandle_t R_RegisterIQM(const char *name, model_t *mod)
{
	union {
		unsigned *u;
		void *v;
	} buf;
	qboolean loaded = qfalse;
	int filesize;

	filesize = ri.FS_ReadFile(name, (void **) &buf.v);
	if(!buf.u)
	{
		mod->type = MOD_BAD;
		return 0;
	}
	
	loaded = R_LoadIQM(mod, buf.u, filesize, name);

	ri.FS_FreeFile (buf.v);
	
	if(!loaded)
	{
		ri.Printf(PRINT_WARNING,"R_RegisterIQM: couldn't load iqm file %s\n", name);
		mod->type = MOD_BAD;
		return 0;
	}
	
	return mod->index;
}