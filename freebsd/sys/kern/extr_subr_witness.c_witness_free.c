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
struct witness {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct witness*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_free ; 
 int /*<<< orphan*/  w_free_cnt ; 
 int /*<<< orphan*/  w_list ; 

__attribute__((used)) static void
witness_free(struct witness *w)
{

	STAILQ_INSERT_HEAD(&w_free, w, w_list);
	w_free_cnt++;
}