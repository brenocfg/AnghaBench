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
typedef  int lwpid_t ;

/* Variables and functions */
 int TID_BUFFER_SIZE ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int* tid_buffer ; 
 int tid_head ; 
 int /*<<< orphan*/  tid_lock ; 
 int tid_tail ; 
 int /*<<< orphan*/  tid_unrhdr ; 

__attribute__((used)) static void
tid_free(lwpid_t tid)
{
	lwpid_t tmp_tid = -1;

	mtx_lock(&tid_lock);
	if ((tid_tail + 1) % TID_BUFFER_SIZE == tid_head) {
		tmp_tid = tid_buffer[tid_head];
		tid_head = (tid_head + 1) % TID_BUFFER_SIZE;
	}
	tid_buffer[tid_tail] = tid;
	tid_tail = (tid_tail + 1) % TID_BUFFER_SIZE;
	mtx_unlock(&tid_lock);
	if (tmp_tid != -1)
		free_unr(tid_unrhdr, tmp_tid);
}