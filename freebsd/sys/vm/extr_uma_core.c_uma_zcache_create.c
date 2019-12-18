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
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  uma_release ;
typedef  int /*<<< orphan*/  uma_init ;
typedef  int /*<<< orphan*/  uma_import ;
typedef  int /*<<< orphan*/  uma_fini ;
typedef  int /*<<< orphan*/  uma_dtor ;
typedef  int /*<<< orphan*/  uma_ctor ;
struct uma_zctor_args {char* name; int size; int flags; scalar_t__ align; void* arg; int /*<<< orphan*/  release; int /*<<< orphan*/  import; int /*<<< orphan*/  fini; int /*<<< orphan*/  uminit; int /*<<< orphan*/  dtor; int /*<<< orphan*/  ctor; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UMA_ANYDOMAIN ; 
 int UMA_ZFLAG_CACHE ; 
 int /*<<< orphan*/  memset (struct uma_zctor_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zone_alloc_item (int /*<<< orphan*/ ,struct uma_zctor_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zones ; 

uma_zone_t
uma_zcache_create(char *name, int size, uma_ctor ctor, uma_dtor dtor,
		    uma_init zinit, uma_fini zfini, uma_import zimport,
		    uma_release zrelease, void *arg, int flags)
{
	struct uma_zctor_args args;

	memset(&args, 0, sizeof(args));
	args.name = name;
	args.size = size;
	args.ctor = ctor;
	args.dtor = dtor;
	args.uminit = zinit;
	args.fini = zfini;
	args.import = zimport;
	args.release = zrelease;
	args.arg = arg;
	args.align = 0;
	args.flags = flags | UMA_ZFLAG_CACHE;

	return (zone_alloc_item(zones, &args, UMA_ANYDOMAIN, M_WAITOK));
}