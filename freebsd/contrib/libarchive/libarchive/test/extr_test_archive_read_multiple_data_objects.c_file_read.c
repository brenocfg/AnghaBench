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
struct mydata {void* buffer; int /*<<< orphan*/  fd; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SIZE ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
file_read(struct archive *a, void *data, const void **buff)
{
  struct mydata *mydata = (struct mydata *)data;
  (void)a;
  *buff = mydata->buffer;
  return read(mydata->fd, mydata->buffer, BLOCK_SIZE);
}