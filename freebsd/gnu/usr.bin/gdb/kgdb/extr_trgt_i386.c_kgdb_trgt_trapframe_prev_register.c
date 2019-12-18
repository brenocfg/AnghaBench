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
struct kgdb_frame_cache {int frame_type; scalar_t__ sp; } ;
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
#define  FT_INTRFRAME 131 
#define  FT_INTRTRAPFRAME 130 
#define  FT_NORMAL 129 
#define  FT_TIMERFRAME 128 
 int I386_EAX_REGNUM ; 
 int I386_FS_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 struct kgdb_frame_cache* kgdb_trgt_frame_cache (struct frame_info*,void**) ; 
 int* kgdb_trgt_frame_offset ; 
 int lval_memory ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int not_lval ; 
 int ofs_fix ; 
 int register_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_read_memory (scalar_t__,void*,int) ; 

__attribute__((used)) static void
kgdb_trgt_trapframe_prev_register(struct frame_info *next_frame,
    void **this_cache, int regnum, int *optimizedp, enum lval_type *lvalp,
    CORE_ADDR *addrp, int *realnump, void *valuep)
{
	char dummy_valuep[MAX_REGISTER_SIZE];
	struct kgdb_frame_cache *cache;
	int ofs, regsz;

	regsz = register_size(current_gdbarch, regnum);

	if (valuep == NULL)
		valuep = dummy_valuep;
	memset(valuep, 0, regsz);
	*optimizedp = 0;
	*addrp = 0;
	*lvalp = not_lval;
	*realnump = -1;

	ofs = (regnum >= I386_EAX_REGNUM && regnum <= I386_FS_REGNUM)
	    ? kgdb_trgt_frame_offset[regnum] + ofs_fix : -1;
	if (ofs == -1)
		return;

	cache = kgdb_trgt_frame_cache(next_frame, this_cache);
	switch (cache->frame_type) {
	case FT_NORMAL:
		break;
	case FT_INTRFRAME:
		ofs += 4;
		break;
	case FT_TIMERFRAME:
		break;
	case FT_INTRTRAPFRAME:
		ofs -= ofs_fix;
		break;
	default:
		fprintf_unfiltered(gdb_stderr, "Correct FT_XXX frame offsets "
		   "for %d\n", cache->frame_type);
		break;
	}
	*addrp = cache->sp + ofs;
	*lvalp = lval_memory;
	target_read_memory(*addrp, valuep, regsz);
}