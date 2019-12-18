#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tlsoffset; size_t tlsinitsize; void const* tlsinit; int static_tls_copied; int tlsindex; scalar_t__ tlssize; scalar_t__ marker; } ;
typedef  TYPE_1__ Obj_Entry ;
typedef  size_t Elf_Addr ;

/* Variables and functions */
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_tls (void*,int,int) ; 
 char* malloc_aligned (size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  next ; 
 size_t round (size_t,size_t) ; 
 size_t tls_dtv_generation ; 
 size_t tls_max_index ; 
 size_t tls_static_max_align ; 
 size_t tls_static_space ; 
 size_t* xcalloc (size_t,int) ; 

void *
allocate_tls(Obj_Entry *objs, void *oldtls, size_t tcbsize, size_t tcbalign)
{
    Obj_Entry *obj;
    size_t size, ralign;
    char *tls;
    Elf_Addr *dtv, *olddtv;
    Elf_Addr segbase, oldsegbase, addr;
    size_t i;

    ralign = tcbalign;
    if (tls_static_max_align > ralign)
	    ralign = tls_static_max_align;
    size = round(tls_static_space, ralign) + round(tcbsize, ralign);

    assert(tcbsize >= 2*sizeof(Elf_Addr));
    tls = malloc_aligned(size, ralign);
    dtv = xcalloc(tls_max_index + 2, sizeof(Elf_Addr));

    segbase = (Elf_Addr)(tls + round(tls_static_space, ralign));
    ((Elf_Addr*)segbase)[0] = segbase;
    ((Elf_Addr*)segbase)[1] = (Elf_Addr) dtv;

    dtv[0] = tls_dtv_generation;
    dtv[1] = tls_max_index;

    if (oldtls) {
	/*
	 * Copy the static TLS block over whole.
	 */
	oldsegbase = (Elf_Addr) oldtls;
	memcpy((void *)(segbase - tls_static_space),
	       (const void *)(oldsegbase - tls_static_space),
	       tls_static_space);

	/*
	 * If any dynamic TLS blocks have been created tls_get_addr(),
	 * move them over.
	 */
	olddtv = ((Elf_Addr**)oldsegbase)[1];
	for (i = 0; i < olddtv[1]; i++) {
	    if (olddtv[i+2] < oldsegbase - size || olddtv[i+2] > oldsegbase) {
		dtv[i+2] = olddtv[i+2];
		olddtv[i+2] = 0;
	    }
	}

	/*
	 * We assume that this block was the one we created with
	 * allocate_initial_tls().
	 */
	free_tls(oldtls, 2*sizeof(Elf_Addr), sizeof(Elf_Addr));
    } else {
	for (obj = objs; obj != NULL; obj = TAILQ_NEXT(obj, next)) {
		if (obj->marker || obj->tlsoffset == 0)
			continue;
		addr = segbase - obj->tlsoffset;
		memset((void*)(addr + obj->tlsinitsize),
		       0, obj->tlssize - obj->tlsinitsize);
		if (obj->tlsinit) {
		    memcpy((void*) addr, obj->tlsinit, obj->tlsinitsize);
		    obj->static_tls_copied = true;
		}
		dtv[obj->tlsindex + 1] = addr;
	}
    }

    return (void*) segbase;
}