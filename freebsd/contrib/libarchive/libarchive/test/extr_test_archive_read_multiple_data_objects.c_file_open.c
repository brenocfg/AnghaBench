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
struct mydata {scalar_t__ fd; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  filename; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  BLOCK_SIZE ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 scalar_t__ calloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
file_open(struct archive *a, void *data)
{
  struct mydata *mydata = (struct mydata *)data;
  (void)a;
  if (mydata->fd < 0)
  {
    mydata->fd = open(mydata->filename, O_RDONLY | O_BINARY);
    if (mydata->fd >= 0)
    {
      if ((mydata->buffer = (void*)calloc(1, BLOCK_SIZE)) == NULL)
        return (ARCHIVE_FAILED);
    }
  }
  return (ARCHIVE_OK);
}