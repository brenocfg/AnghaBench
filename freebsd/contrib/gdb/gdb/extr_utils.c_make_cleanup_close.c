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
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int /*<<< orphan*/  do_close_cleanup ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int*) ; 
 int* xmalloc (int) ; 

struct cleanup *
make_cleanup_close (int fd)
{
  int *saved_fd = xmalloc (sizeof (fd));
  *saved_fd = fd;
  return make_cleanup (do_close_cleanup, saved_fd);
}