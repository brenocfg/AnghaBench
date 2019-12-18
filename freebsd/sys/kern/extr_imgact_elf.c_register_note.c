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
struct note_info_list {int dummy; } ;
struct note_info {int type; size_t outsize; void* outarg; int /*<<< orphan*/  (* outfunc ) (void*,int /*<<< orphan*/ *,size_t*) ;} ;
typedef  int /*<<< orphan*/  (* outfunc_t ) (void*,int /*<<< orphan*/ *,size_t*) ;
typedef  int /*<<< orphan*/  FREEBSD_ABI_VENDOR ;
typedef  int /*<<< orphan*/  Elf_Note ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_NOTE_ROUNDSIZE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct note_info_list*,struct note_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct note_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int roundup2 (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
register_note(struct note_info_list *list, int type, outfunc_t out, void *arg)
{
	struct note_info *ninfo;
	size_t size, notesize;

	size = 0;
	out(arg, NULL, &size);
	ninfo = malloc(sizeof(*ninfo), M_TEMP, M_ZERO | M_WAITOK);
	ninfo->type = type;
	ninfo->outfunc = out;
	ninfo->outarg = arg;
	ninfo->outsize = size;
	TAILQ_INSERT_TAIL(list, ninfo, link);

	if (type == -1)
		return (size);

	notesize = sizeof(Elf_Note) +		/* note header */
	    roundup2(sizeof(FREEBSD_ABI_VENDOR), ELF_NOTE_ROUNDSIZE) +
						/* note name */
	    roundup2(size, ELF_NOTE_ROUNDSIZE);	/* note description */

	return (notesize);
}