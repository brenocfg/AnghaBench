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
struct mpu401 {int /*<<< orphan*/  mid; scalar_t__ flags; void* cookie; int /*<<< orphan*/  si; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  mpu401_intr_t ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_MIDI ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct mpu401*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mpu401* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  midi_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mpu401*) ; 
 int /*<<< orphan*/  mpu401_class ; 
 int /*<<< orphan*/ * mpu401_intr ; 
 int /*<<< orphan*/  printf (char*) ; 

struct mpu401 *
mpu401_init(kobj_class_t cls, void *cookie, driver_intr_t softintr,
    mpu401_intr_t ** cb)
{
	struct mpu401 *m;

	*cb = NULL;
	m = malloc(sizeof(*m), M_MIDI, M_NOWAIT | M_ZERO);

	if (!m)
		return NULL;

	kobj_init((kobj_t)m, cls);

	callout_init(&m->timer, 1);

	m->si = softintr;
	m->cookie = cookie;
	m->flags = 0;

	m->mid = midi_init(&mpu401_class, 0, 0, m);
	if (!m->mid)
		goto err;
	*cb = mpu401_intr;
	return m;
err:
	printf("mpu401_init error\n");
	free(m, M_MIDI);
	return NULL;
}