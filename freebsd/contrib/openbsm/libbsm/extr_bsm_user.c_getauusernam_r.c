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
struct au_user_ent {int /*<<< orphan*/  au_name; } ;

/* Variables and functions */
 struct au_user_ent* getauuserent_r_locked (struct au_user_ent*) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setauuser_locked () ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

struct au_user_ent *
getauusernam_r(struct au_user_ent *u, const char *name)
{
	struct au_user_ent *up;

	if (name == NULL)
		return (NULL);

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif

	setauuser_locked();
	while ((up = getauuserent_r_locked(u)) != NULL) {
		if (strcmp(name, u->au_name) == 0) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
			pthread_mutex_unlock(&mutex);
#endif
			return (up);
		}
	}

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif
	return (NULL);

}