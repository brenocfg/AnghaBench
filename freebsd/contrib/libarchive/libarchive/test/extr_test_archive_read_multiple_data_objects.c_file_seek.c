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
struct mydata {int /*<<< orphan*/  fd; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_FATAL ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int64_t
file_seek(struct archive *a, void *data, int64_t request, int whence)
{
  struct mydata *mine = (struct mydata *)data;
  int64_t r;

  (void)a;
  r = lseek(mine->fd, request, whence);
  if (r >= 0)
    return r;
  return (ARCHIVE_FATAL);
}