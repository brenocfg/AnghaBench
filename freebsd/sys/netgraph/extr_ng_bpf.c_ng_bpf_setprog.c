#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ng_bpf_hookprog {scalar_t__ bpf_prog_len; int /*<<< orphan*/  ifNotMatch; int /*<<< orphan*/  ifMatch; int /*<<< orphan*/  bpf_prog; } ;
typedef  int /*<<< orphan*/  hook_p ;
typedef  TYPE_1__* hinfo_p ;
typedef  int /*<<< orphan*/  bpf_jit_filter ;
struct TYPE_3__ {struct ng_bpf_hookprog* prog; void* nomatch; void* match; int /*<<< orphan*/ * jit_prog; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NETGRAPH_BPF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int NG_BPF_HOOKPROG_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct ng_bpf_hookprog const*,struct ng_bpf_hookprog*,int) ; 
 int /*<<< orphan*/  bpf_destroy_jit_filter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bpf_jitter (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bpf_maxinsns ; 
 int /*<<< orphan*/  bpf_validate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (struct ng_bpf_hookprog*,int /*<<< orphan*/ ) ; 
 struct ng_bpf_hookprog* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ng_findhook (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_bpf_setprog(hook_p hook, const struct ng_bpf_hookprog *hp0)
{
	const hinfo_p hip = NG_HOOK_PRIVATE(hook);
	struct ng_bpf_hookprog *hp;
#ifdef BPF_JITTER
	bpf_jit_filter *jit_prog;
#endif
	int size;

	/* Check program for validity */
	if (hp0->bpf_prog_len > bpf_maxinsns ||
	    !bpf_validate(hp0->bpf_prog, hp0->bpf_prog_len))
		return (EINVAL);

	/* Make a copy of the program */
	size = NG_BPF_HOOKPROG_SIZE(hp0->bpf_prog_len);
	hp = malloc(size, M_NETGRAPH_BPF, M_NOWAIT);
	if (hp == NULL)
		return (ENOMEM);
	bcopy(hp0, hp, size);
#ifdef BPF_JITTER
	jit_prog = bpf_jitter(hp->bpf_prog, hp->bpf_prog_len);
#endif

	/* Free previous program, if any, and assign new one */
	if (hip->prog != NULL)
		free(hip->prog, M_NETGRAPH_BPF);
	hip->prog = hp;
#ifdef BPF_JITTER
	if (hip->jit_prog != NULL)
		bpf_destroy_jit_filter(hip->jit_prog);
	hip->jit_prog = jit_prog;
#endif

	/* Prepare direct references on target hooks. */
	hip->match = ng_findhook(NG_HOOK_NODE(hook), hip->prog->ifMatch);
	hip->nomatch = ng_findhook(NG_HOOK_NODE(hook), hip->prog->ifNotMatch);
	return (0);
}