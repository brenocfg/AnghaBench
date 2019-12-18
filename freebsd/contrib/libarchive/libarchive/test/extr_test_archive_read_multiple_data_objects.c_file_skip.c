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
struct mydata {int /*<<< orphan*/  filename; int /*<<< orphan*/  fd; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int64_t
file_skip(struct archive *a, void *data, int64_t request)
{
  struct mydata *mydata = (struct mydata *)data;
  int64_t result = lseek(mydata->fd, SEEK_CUR, request);
  if (result >= 0)
    return result;
  archive_set_error(a, errno, "Error seeking in '%s'", mydata->filename);
  return -1;
}