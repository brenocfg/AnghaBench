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
typedef  union ecore_qable_obj {int dummy; } ecore_qable_obj ;
struct ecore_exe_queue_obj {int exe_chunk_len; int /*<<< orphan*/  get; int /*<<< orphan*/  execute; int /*<<< orphan*/  optimize; int /*<<< orphan*/  remove; int /*<<< orphan*/  validate; union ecore_qable_obj* owner; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_comp; int /*<<< orphan*/  exe_queue; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  exe_q_validate ;
typedef  int /*<<< orphan*/  exe_q_remove ;
typedef  int /*<<< orphan*/  exe_q_optimize ;
typedef  int /*<<< orphan*/  exe_q_get ;
typedef  int /*<<< orphan*/  exe_q_execute ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct ecore_exe_queue_obj*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ECORE_SPIN_LOCK_INIT (int /*<<< orphan*/ *,struct bxe_softc*) ; 

__attribute__((used)) static inline void ecore_exe_queue_init(struct bxe_softc *sc,
					struct ecore_exe_queue_obj *o,
					int exe_len,
					union ecore_qable_obj *owner,
					exe_q_validate validate,
					exe_q_remove remove,
					exe_q_optimize optimize,
					exe_q_execute exec,
					exe_q_get get)
{
	ECORE_MEMSET(o, 0, sizeof(*o));

	ECORE_LIST_INIT(&o->exe_queue);
	ECORE_LIST_INIT(&o->pending_comp);

	ECORE_SPIN_LOCK_INIT(&o->lock, sc);

	o->exe_chunk_len = exe_len;
	o->owner         = owner;

	/* Owner specific callbacks */
	o->validate      = validate;
	o->remove        = remove;
	o->optimize      = optimize;
	o->execute       = exec;
	o->get           = get;

	ECORE_MSG(sc, "Setup the execution queue with the chunk length of %d\n",
		  exe_len);
}