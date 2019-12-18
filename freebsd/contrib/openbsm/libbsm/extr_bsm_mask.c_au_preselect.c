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
struct au_event_ent {int ae_class; } ;
struct TYPE_3__ {int am_success; int am_failure; } ;
typedef  TYPE_1__ au_mask_t ;
typedef  int /*<<< orphan*/  au_event_t ;
typedef  int au_class_t ;

/* Variables and functions */
 int AU_PRS_FAILURE ; 
#define  AU_PRS_REREAD 129 
 int AU_PRS_SUCCESS ; 
#define  AU_PRS_USECACHE 128 
 scalar_t__ firsttime ; 
 int /*<<< orphan*/  flush_cache () ; 
 int load_event_table () ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct au_event_ent* read_from_cache (int /*<<< orphan*/ ) ; 

int
au_preselect(au_event_t event, au_mask_t *mask_p, int sorf, int flag)
{
	struct au_event_ent *ev;
	au_class_t effmask = 0;

	if (mask_p == NULL)
		return (-1);


#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif
	if (firsttime) {
		firsttime = 0;
		if ( -1 == load_event_table()) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
			pthread_mutex_unlock(&mutex);
#endif
			return (-1);
		}
	}
	switch (flag) {
	case AU_PRS_REREAD:
		flush_cache();
		if (load_event_table() == -1) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
			pthread_mutex_unlock(&mutex);
#endif
			return (-1);
		}
		ev = read_from_cache(event);
		break;
	case AU_PRS_USECACHE:
		ev = read_from_cache(event);
		break;
	default:
		ev = NULL;
	}
	if (ev == NULL) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-1);
	}
	if (sorf & AU_PRS_SUCCESS)
		effmask |= (mask_p->am_success & ev->ae_class);
	if (sorf & AU_PRS_FAILURE)
		effmask |= (mask_p->am_failure & ev->ae_class);
#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif
	if (effmask != 0)
		return (1);
	return (0);
}