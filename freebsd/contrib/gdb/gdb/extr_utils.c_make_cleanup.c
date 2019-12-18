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
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  make_cleanup_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_chain ; 
 struct cleanup* make_my_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

struct cleanup *
make_cleanup (make_cleanup_ftype *function, void *arg)
{
  return make_my_cleanup (&cleanup_chain, function, arg);
}