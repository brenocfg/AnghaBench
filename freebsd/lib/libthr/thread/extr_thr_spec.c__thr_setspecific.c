#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pthread_specific_elem {int dummy; } ;
struct pthread {TYPE_1__* specific; int /*<<< orphan*/  specific_data_count; } ;
typedef  size_t pthread_key_t ;
struct TYPE_4__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  allocated; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int PTHREAD_KEYS_MAX ; 
 void* __thr_calloc (unsigned int,int) ; 
 struct pthread* _get_curthread () ; 
 TYPE_2__* _thread_keytable ; 

int 
_thr_setspecific(pthread_key_t userkey, const void *value)
{
	struct pthread *pthread;
	void *tmp;
	pthread_key_t key;

	key = userkey - 1;
	if ((unsigned int)key >= PTHREAD_KEYS_MAX ||
	    !_thread_keytable[key].allocated)
		return (EINVAL);

	pthread = _get_curthread();
	if (pthread->specific == NULL) {
		tmp = __thr_calloc(PTHREAD_KEYS_MAX,
		    sizeof(struct pthread_specific_elem));
		if (tmp == NULL)
			return (ENOMEM);
		pthread->specific = tmp;
	}
	if (pthread->specific[key].data == NULL) {
		if (value != NULL)
			pthread->specific_data_count++;
	} else if (value == NULL)
		pthread->specific_data_count--;
	pthread->specific[key].data = value;
	pthread->specific[key].seqno = _thread_keytable[key].seqno;
	return (0);
}