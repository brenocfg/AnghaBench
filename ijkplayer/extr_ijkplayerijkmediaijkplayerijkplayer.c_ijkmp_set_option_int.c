#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ffplayer; } ;
typedef  TYPE_1__ IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ffp_set_option_int (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void ijkmp_set_option_int(IjkMediaPlayer *mp, int opt_category, const char *name, int64_t value)
{
    assert(mp);

    // MPTRACE("%s(%s, %"PRId64")\n", __func__, name, value);
    pthread_mutex_lock(&mp->mutex);
    ffp_set_option_int(mp->ffplayer, opt_category, name, value);
    pthread_mutex_unlock(&mp->mutex);
    // MPTRACE("%s()=void\n", __func__);
}