#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  code; } ;
struct slist {TYPE_7__ s; struct slist* next; } ;
struct edge {TYPE_1__* pred; struct edge* next; } ;
struct TYPE_14__ {int /*<<< orphan*/  code; int /*<<< orphan*/  k; } ;
struct TYPE_13__ {int /*<<< orphan*/  code; } ;
struct TYPE_12__ {int /*<<< orphan*/  code; } ;
struct block {scalar_t__* val; scalar_t__ out_use; scalar_t__ oval; TYPE_4__ s; TYPE_3__ ef; TYPE_2__ et; struct slist* stmts; struct edge* in_edges; } ;
struct TYPE_15__ {scalar_t__ done; } ;
typedef  TYPE_5__ opt_state_t ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  scalar_t__ bpf_int32 ;
struct TYPE_11__ {scalar_t__* val; } ;

/* Variables and functions */
 size_t A_ATOM ; 
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_JMP ; 
 scalar_t__ BPF_K ; 
 scalar_t__ BPF_RET ; 
 scalar_t__ BPF_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ K (int /*<<< orphan*/ ) ; 
 int N_ATOMS ; 
 scalar_t__ VAL_UNKNOWN ; 
 size_t X_ATOM ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opt_deadstores (TYPE_5__*,struct block*) ; 
 int /*<<< orphan*/  opt_peep (TYPE_5__*,struct block*) ; 
 int /*<<< orphan*/  opt_stmt (int /*<<< orphan*/ *,TYPE_5__*,TYPE_7__*,scalar_t__*,int) ; 

__attribute__((used)) static void
opt_blk(compiler_state_t *cstate, opt_state_t *opt_state,
    struct block *b, int do_stmts)
{
	struct slist *s;
	struct edge *p;
	int i;
	bpf_int32 aval, xval;

#if 0
	for (s = b->stmts; s && s->next; s = s->next)
		if (BPF_CLASS(s->s.code) == BPF_JMP) {
			do_stmts = 0;
			break;
		}
#endif

	/*
	 * Initialize the atom values.
	 */
	p = b->in_edges;
	if (p == 0) {
		/*
		 * We have no predecessors, so everything is undefined
		 * upon entry to this block.
		 */
		memset((char *)b->val, 0, sizeof(b->val));
	} else {
		/*
		 * Inherit values from our predecessors.
		 *
		 * First, get the values from the predecessor along the
		 * first edge leading to this node.
		 */
		memcpy((char *)b->val, (char *)p->pred->val, sizeof(b->val));
		/*
		 * Now look at all the other nodes leading to this node.
		 * If, for the predecessor along that edge, a register
		 * has a different value from the one we have (i.e.,
		 * control paths are merging, and the merging paths
		 * assign different values to that register), give the
		 * register the undefined value of 0.
		 */
		while ((p = p->next) != NULL) {
			for (i = 0; i < N_ATOMS; ++i)
				if (b->val[i] != p->pred->val[i])
					b->val[i] = 0;
		}
	}
	aval = b->val[A_ATOM];
	xval = b->val[X_ATOM];
	for (s = b->stmts; s; s = s->next)
		opt_stmt(cstate, opt_state, &s->s, b->val, do_stmts);

	/*
	 * This is a special case: if we don't use anything from this
	 * block, and we load the accumulator or index register with a
	 * value that is already there, or if this block is a return,
	 * eliminate all the statements.
	 *
	 * XXX - what if it does a store?
	 *
	 * XXX - why does it matter whether we use anything from this
	 * block?  If the accumulator or index register doesn't change
	 * its value, isn't that OK even if we use that value?
	 *
	 * XXX - if we load the accumulator with a different value,
	 * and the block ends with a conditional branch, we obviously
	 * can't eliminate it, as the branch depends on that value.
	 * For the index register, the conditional branch only depends
	 * on the index register value if the test is against the index
	 * register value rather than a constant; if nothing uses the
	 * value we put into the index register, and we're not testing
	 * against the index register's value, and there aren't any
	 * other problems that would keep us from eliminating this
	 * block, can we eliminate it?
	 */
	if (do_stmts &&
	    ((b->out_use == 0 &&
	      aval != VAL_UNKNOWN && b->val[A_ATOM] == aval &&
	      xval != VAL_UNKNOWN && b->val[X_ATOM] == xval) ||
	     BPF_CLASS(b->s.code) == BPF_RET)) {
		if (b->stmts != 0) {
			b->stmts = 0;
			opt_state->done = 0;
		}
	} else {
		opt_peep(opt_state, b);
		opt_deadstores(opt_state, b);
	}
	/*
	 * Set up values for branch optimizer.
	 */
	if (BPF_SRC(b->s.code) == BPF_K)
		b->oval = K(b->s.k);
	else
		b->oval = b->val[X_ATOM];
	b->et.code = b->s.code;
	b->ef.code = -b->s.code;
}