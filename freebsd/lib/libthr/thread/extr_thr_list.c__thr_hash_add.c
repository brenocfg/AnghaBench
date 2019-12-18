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
struct thread_hash_head {int dummy; } ;
struct pthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct thread_hash_head*,struct pthread*,int /*<<< orphan*/ ) ; 
 size_t THREAD_HASH (struct pthread*) ; 
 int /*<<< orphan*/  hle ; 
 struct thread_hash_head* thr_hashtable ; 

void
_thr_hash_add(struct pthread *thread)
{
	struct thread_hash_head *head;

	head = &thr_hashtable[THREAD_HASH(thread)];
	LIST_INSERT_HEAD(head, thread, hle);
}