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
struct sigevent {scalar_t__ sigev_notify_attributes; int /*<<< orphan*/  sigev_notify_function; int /*<<< orphan*/  sigev_value; } ;
struct sigev_node {int sn_type; int /*<<< orphan*/  sn_attr; TYPE_1__* sn_tn; int /*<<< orphan*/  sn_gen; int /*<<< orphan*/  sn_func; int /*<<< orphan*/  sn_value; } ;
struct TYPE_2__ {int /*<<< orphan*/  tn_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 int /*<<< orphan*/  _pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fetch_add_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attrcopy (scalar_t__,int /*<<< orphan*/ *) ; 
 struct sigev_node* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct sigev_node*) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  sigev_generation ; 
 TYPE_1__* sigev_thread_create (int) ; 

struct sigev_node *
__sigev_alloc(int type, const struct sigevent *evp, struct sigev_node *prev,
	int usedefault)
{
	struct sigev_node *sn;

	sn = calloc(1, sizeof(*sn));
	if (sn != NULL) {
		sn->sn_value = evp->sigev_value;
		sn->sn_func  = evp->sigev_notify_function;
		sn->sn_gen   = atomic_fetch_add_explicit(&sigev_generation, 1,
		    memory_order_relaxed);
		sn->sn_type  = type;
		_pthread_attr_init(&sn->sn_attr);
		_pthread_attr_setdetachstate(&sn->sn_attr, PTHREAD_CREATE_DETACHED);
		if (evp->sigev_notify_attributes)
			attrcopy(evp->sigev_notify_attributes, &sn->sn_attr);
		if (prev) {
			__sigev_list_lock();
			prev->sn_tn->tn_refcount++;
			__sigev_list_unlock();
			sn->sn_tn = prev->sn_tn;
		} else {
			sn->sn_tn = sigev_thread_create(usedefault);
			if (sn->sn_tn == NULL) {
				_pthread_attr_destroy(&sn->sn_attr);
				free(sn);
				sn = NULL;
			}
		}
	}
	return (sn);
}